#ifndef WAVY_LINES_ANIMATION_H
#define WAVY_LINES_ANIMATION_H

#include "animation.h"

#define MAX_WAVY_LINES 50

struct WavyLine {
    float baseY;
    float amplitude;
    float frequency;
    float phase;
    Color color;
};

class WavyLinesAnimation : public Animation {
public:
    WavyLinesAnimation();
    void Update() override;
    void Draw() override;
    void UpdateSpeedAttributes() override;

private:
    WavyLine lines[MAX_WAVY_LINES];
    float timee;
};

#endif
