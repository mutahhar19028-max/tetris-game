#include "intro-video.h"

IntroVideo::IntroVideo(const char* videoPath) {
    videoPlayer = new VideoPlayer(videoPath);
    Play();
}

IntroVideo::~IntroVideo() {
    delete videoPlayer;
}

void IntroVideo::Update(float deltaTime) {
    if (videoPlayer && !videoPlayer->IsFinished()) {
        videoPlayer->Update(deltaTime);

        // Optional: allow skip with Enter
        if (IsKeyPressed(KEY_ENTER)) {
            videoPlayer->finished = true;
        }
    }
}

void IntroVideo::Draw() {
    if (videoPlayer && !videoPlayer->IsFinished()) {
        Texture2D frame = videoPlayer->GetCurrentFrameTexture();
        DrawTexture(frame, 0, 0, WHITE);
    }
}

bool IntroVideo::IsFinished() const {
    return videoPlayer ? videoPlayer->IsFinished() : true;
}

void IntroVideo::Play() {
    while(!WindowShouldClose() && !videoPlayer->finished) {

        float delta = GetFrameTime();
        Update(delta);

        BeginDrawing();

        ClearBackground(BLACK);
        Draw();
        
        EndDrawing();
    }
}
