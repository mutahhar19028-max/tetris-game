#include "dots-animation.h"

SpiralDotsAnimation::SpiralDotsAnimation() {
    srand(time(NULL));
    center = { (float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f };

    for (int i = 0; i < MAX_SPIRAL_DOTS; i++) {
        dots[i] = {
            .angle = static_cast<float>(rand() % 360) * DEG2RAD,
            .radius = static_cast<float>(rand() % 200 + 50), // 50–250
            .speed = ((float)(rand() % 100) / 2000.0f) + 0.002f * sp, // 0.002–0.052 rad/frame
            .color = {
                (unsigned char)(rand() % 150 + 105),
                (unsigned char)(rand() % 150 + 105),
                (unsigned char)(rand() % 150 + 105),
                255
            }
        };
    }
}

void SpiralDotsAnimation::UpdateSpeedAttributes() {
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


void SpiralDotsAnimation::Update() {
    for (int i = 0; i < MAX_SPIRAL_DOTS; i++) {
        dots[i].angle += dots[i].speed;
        if (dots[i].angle > 2 * PI) dots[i].angle -= 2 * PI;
    }
}

void SpiralDotsAnimation::Draw() {
    for (int i = 0; i < MAX_SPIRAL_DOTS; i++) {
        float x = center.x + cosf(dots[i].angle) * dots[i].radius;
        float y = center.y + sinf(dots[i].angle) * dots[i].radius;

        // Trailing effect
        for (int j = 0; j < 10; j++) {
            float trailAngle = dots[i].angle - j * 0.1f;
            float trailX = center.x + cosf(trailAngle) * dots[i].radius;
            float trailY = center.y + sinf(trailAngle) * dots[i].radius;
            float alpha = 0.1f + (0.1f * (10 - j));
            Color faded = Fade(dots[i].color, alpha);
            DrawCircleV({ trailX, trailY }, 2.0f, faded);
        }

        DrawCircleV({ x, y }, 3.0f, Fade(dots[i].color, 0.7f));
    }
}
