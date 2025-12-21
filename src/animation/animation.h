#ifndef ANIMATION_H
#define ANIMATION_H

#include <cmath>
#include <cstdlib>
#include <ctime>
#include "../../include/raylib/raylib.h"

enum class Speed {
    SLOW,
    MEDIUM,
    HIGH
};

class Animation {
protected:
    float sp;
    Speed speed = Speed::MEDIUM;

    virtual void UpdateSpeedAttributes() = 0;

public:
    Animation();
    Animation(float);

    virtual void Update() = 0;
    virtual void Draw() = 0;

    void SetSpeed(Speed newSpeed);
    Speed GetSpeed() const;

    virtual ~Animation() = default;
};

// === INLINE DEFINITIONS ===

inline Animation::Animation() : sp(1.0f), speed(Speed::MEDIUM) {}

inline Animation::Animation(float speed) : sp(speed), speed(Speed::MEDIUM) {}

inline Speed Animation::GetSpeed() const { return speed; }

inline void Animation::SetSpeed(Speed newSpeed) {
    speed = newSpeed;
    UpdateSpeedAttributes();
}

#endif // ANIMATION_H
