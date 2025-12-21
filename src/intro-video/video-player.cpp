#include "video-player.h"
#include <iostream>
#include <stdexcept>
#include <cstring>

VideoPlayer::VideoPlayer(const char* path) {
    avformat_network_init();
    LoadVideo(path);
}

VideoPlayer::~VideoPlayer() {
    if (currentTexture.id > 0) UnloadTexture(currentTexture);
    if (frame) av_frame_free(&frame);
    if (packet) av_packet_free(&packet);
    if (codecCtx) avcodec_free_context(&codecCtx);
    if (formatCtx) avformat_close_input(&formatCtx);
    if (swsCtx) sws_freeContext(swsCtx);
}

void VideoPlayer::LoadVideo(const char* path) {
    if (avformat_open_input(&formatCtx, path, nullptr, nullptr) != 0)
        throw std::runtime_error("Failed to open video file.");

    if (avformat_find_stream_info(formatCtx, nullptr) < 0)
        throw std::runtime_error("Failed to retrieve stream info.");

    videoStreamIndex = -1;
    for (unsigned int i = 0; i < formatCtx->nb_streams; ++i) {
        if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            break;
        }
    }

    if (videoStreamIndex == -1)
        throw std::runtime_error("No video stream found.");

    AVCodecParameters* codecPar = formatCtx->streams[videoStreamIndex]->codecpar;
    const AVCodec* codec = avcodec_find_decoder(codecPar->codec_id);
    if (!codec)
        throw std::runtime_error("Unsupported codec.");

    codecCtx = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecCtx, codecPar);
    if (avcodec_open2(codecCtx, codec, nullptr) < 0)
        throw std::runtime_error("Failed to open codec.");

    frame = av_frame_alloc();
    packet = av_packet_alloc();

    // Assume 30 FPS unless specified
    AVRational framerate = av_guess_frame_rate(formatCtx, formatCtx->streams[videoStreamIndex], nullptr);
    frameDelay = av_q2d({framerate.den, framerate.num});
    if (frameDelay <= 0.0f) frameDelay = 1.0f / 30.0f;

    swsCtx = sws_getContext(
        codecCtx->width, codecCtx->height, codecCtx->pix_fmt,
        codecCtx->width, codecCtx->height, AV_PIX_FMT_RGB24,
        SWS_BILINEAR, nullptr, nullptr, nullptr
    );

    frameImage.data = RL_MALLOC(codecCtx->width * codecCtx->height * 3);
    frameImage.width = codecCtx->width;
    frameImage.height = codecCtx->height;
    frameImage.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8;
    frameImage.mipmaps = 1;

    currentTexture = LoadTextureFromImage(frameImage);

    DecodeNextFrame();
}

bool VideoPlayer::Update(float deltaTime) {
    if (finished) return false;

    frameTimer += deltaTime;
    if (frameTimer >= frameDelay) {
        frameTimer = 0.0f;
        DecodeNextFrame();
    }

    return true;
}

void VideoPlayer::DecodeNextFrame() {
    int response = 0;

    while (av_read_frame(formatCtx, packet) >= 0) {
        if (packet->stream_index != videoStreamIndex) {
            av_packet_unref(packet);
            continue;
        }

        response = avcodec_send_packet(codecCtx, packet);
        if (response < 0) {
            av_packet_unref(packet);
            continue;
        }

        response = avcodec_receive_frame(codecCtx, frame);
        av_packet_unref(packet);

        if (response == AVERROR(EAGAIN)) {
            continue;
        } else if (response == AVERROR_EOF) {
            finished = true;
            return;
        } else if (response < 0) {
            finished = true;
            return;
        }

        // Convert to RGB
        uint8_t* dst[1] = { (uint8_t*)frameImage.data };
        int dstStride[1] = { 3 * codecCtx->width };

        sws_scale(
            swsCtx,
            frame->data, frame->linesize,
            0, codecCtx->height,
            dst, dstStride
        );

        UpdateTexture(currentTexture, frameImage.data);
        return;
    }

    finished = true;
}

Texture2D VideoPlayer::GetCurrentFrameTexture() const {
    return currentTexture;
}

bool VideoPlayer::IsFinished() const {
    return finished;
}
