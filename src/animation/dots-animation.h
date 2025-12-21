#ifndef SPIRAL_DOTS_ANIMATION_H
#define SPIRAL_DOTS_ANIMATION_H

#include "animation.h"

#define MAX_SPIRAL_DOTS 80

struct SpiralDot {
    float angle;
    float radius;
    float speed;
    Color color;
};

class SpiralDotsAnimation : public Animation {
public:
    SpiralDotsAnimation();
    void Update() override;
    void Draw() override;
    void UpdateSpeedAttributes() override;

private:
    SpiralDot dots[MAX_SPIRAL_DOTS];
    Vector2 center;
};

#endif
