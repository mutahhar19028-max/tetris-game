#ifndef FLOATING_SQUARE_ANIMATION_H
#define FLOATING_SQUARE_ANIMATION_H

#include "animation.h"
#include "../../include/raylib/raylib.h"

#define MAX_SQUARES 30
#define SQUARE_PADDING 40

struct AnimationSquare {
    Vector2 position;
    Vector2 velocity;
    float size;
    float rotation;
    float rotationSpeed;
    Color color;
};

class FloatingSquareAnimation : public Animation {
public:

    FloatingSquareAnimation();
    void Update() override;
    void Draw() override;
    void UpdateSpeedAttributes() override;

private:
    AnimationSquare squares[MAX_SQUARES];
};

#endif
