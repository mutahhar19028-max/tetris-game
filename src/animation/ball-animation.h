#ifndef BALL_ANIMATION_H
#define BALL_ANIMATION_H

#include "animation.h"
#include "../../include/raylib/raylib.h"

#define MAX_BALLS 25
#define PADDING 50

struct AnimationBall {
    Vector2 position;
    Vector2 velocity;
    float radius;
    Color color;
};

class BallAnimation : public Animation {
public:
    BallAnimation();
    void Update() override;
    void Draw() override;
    void UpdateSpeedAttributes() override;

private:
    AnimationBall animationBalls[MAX_BALLS];
};

#endif