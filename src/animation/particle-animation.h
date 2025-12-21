#ifndef PARTICLE_BURST_ANIMATION_H
#define PARTICLE_BURST_ANIMATION_H

#include "animation.h"
#include "../../include/raylib/raylib.h"

#define MAX_PARTICLES 120
#define PARTICLE_LIFETIME 120.0f

struct Particle {
    Vector2 position;
    Vector2 velocity;
    float radius;
    float lifetime;
    float initialLifetime;
    Color color;
};

class ParticleBurstAnimation : public Animation {
public:
    ParticleBurstAnimation();
    void Update() override;
    void Draw() override;
    void UpdateSpeedAttributes() override;

private:
    Particle particles[MAX_PARTICLES];
    void ResetParticle(int index);
};

#endif