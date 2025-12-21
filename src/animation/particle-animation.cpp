#include "particle-animation.h"

void ParticleBurstAnimation::ResetParticle(int index) {
    float angle = static_cast<float>(rand() % 360) * DEG2RAD;
    float speed = static_cast<float>(rand() % 40 + 10) / 10.0f * sp; // 1.0f to 5.0f
    float radius = static_cast<float>(rand() % 3 + 2); // 2–4 px
    float lifetime = static_cast<float>(rand() % 60 + 60); // 60–120 frames

    particles[index] = {
        .position = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f },
        .velocity = { cosf(angle) * speed, sinf(angle) * speed },
        .radius = radius,
        .lifetime = lifetime,
        .initialLifetime = lifetime,
        .color = {
            (unsigned char)(rand() % 150 + 105),
            (unsigned char)(rand() % 150 + 105),
            (unsigned char)(rand() % 150 + 105),
            255
        }
    };
}

ParticleBurstAnimation::ParticleBurstAnimation() {
    srand(time(NULL));
    for(int i = 0; i < MAX_PARTICLES; i++)
        ResetParticle(i);
}

void ParticleBurstAnimation::UpdateSpeedAttributes() {
    switch(speed) {
        case Speed::SLOW:
            sp = 0.5f;
            break;
        case Speed::MEDIUM:
            sp = 1.0f;
            break;
        case Speed::HIGH:
            sp = 1.5f;
            break;
    }
}

void ParticleBurstAnimation::Update() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].position.x += particles[i].velocity.x;
        particles[i].position.y += particles[i].velocity.y;
        particles[i].lifetime -= 1.0f;

        if (particles[i].lifetime <= 0.0f) {
            ResetParticle(i);
        }
    }
}

void ParticleBurstAnimation::Draw() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        float alpha = particles[i].lifetime / particles[i].initialLifetime;
        Color fadedColor = Fade(particles[i].color, alpha * 0.6f); // Fade out over time
        DrawCircleV(particles[i].position, particles[i].radius, fadedColor);
    }
}
