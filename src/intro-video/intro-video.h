#ifndef INTRO_VIDEO_H
#define INTRO_VIDEO_H

#include "../../include/raylib/raylib.h"
#include "video-player.h"

class IntroVideo {
public:
    IntroVideo(const char* videoPath);
    ~IntroVideo();

    void Update(float deltaTime);
    void Draw();
    void Play();
    bool IsFinished() const;

private:
    VideoPlayer* videoPlayer;
};

#endif // INTRO_VIDEO_H
