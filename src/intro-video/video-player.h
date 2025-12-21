#ifndef VIDEO_PLAYER_H
#define VIDEO_PLAYER_H

#include "../../include/raylib/raylib.h"
#include <string>

extern "C" {
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/imgutils.h>
}

class VideoPlayer {
public:
    bool finished = false;

    VideoPlayer(const char* path);
    ~VideoPlayer();

    bool Update(float deltaTime);
    Texture2D GetCurrentFrameTexture() const;
    bool IsFinished() const;

private:
    void LoadVideo(const char* path);
    void DecodeNextFrame();

    AVFormatContext* formatCtx = nullptr;
    AVCodecContext* codecCtx = nullptr;
    AVFrame* frame = nullptr;
    AVPacket* packet = nullptr;
    SwsContext* swsCtx = nullptr;
    int videoStreamIndex = -1;

    Texture2D currentTexture;
    Image frameImage;

    float frameTimer = 0.0f;
    float frameDelay = 1.0f / 30.0f; // 30 FPS fallback
};


#endif // VIDEO_PLAYER_H
