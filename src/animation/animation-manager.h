#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "animation.h"
#include "ball-animation.h"
#include "particle-animation.h"
#include "dots-animation.h"
#include "lines-animation.h"
#include "square-animation.h"

enum class AnimationType {
    SQUARE,
    PARTICLE_BURST,
    SPIRAL_DOTS,
    WAVY_LINES,
    BALL,
    COUNT
};

class AnimationManager {
private:
    Animation* currentAnimation;
    AnimationType currentType;
    Animation* animations[static_cast<int>(AnimationType::COUNT)];

    Speed speed = Speed::MEDIUM;

    void UpdateSpeedAttributes();

public:

    static const char* animationNames[];
    static int currentAnimationIndex;

    AnimationManager();
    ~AnimationManager();

    void SetAnimation(AnimationType type);
    void Update();
    void Draw();
    void CycleNextAnimation();
    void CyclePreviousAnimation();
    void SetSpeed(Speed s);
    Speed GetSpeed() const;
};

#endif
