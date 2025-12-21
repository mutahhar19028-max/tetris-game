#include "ball-animation.h"

#define MAX_SPEED 30.0f

BallAnimation::BallAnimation() {
    srand(time(NULL));
    for (int i = 0; i < MAX_BALLS; i++) {
        float radius = static_cast<float>(rand() % 30 + 15);
        float speed = MAX_SPEED / radius * sp;

        animationBalls[i] = {
            .position = {
                static_cast<float>(rand() % (GetScreenWidth() - 2 * PADDING) + PADDING),
                static_cast<float>(rand() % (GetScreenHeight() - 2 * PADDING) + PADDING)
            },
            .velocity = {
                (rand() % 2 == 0 ? 1 : -1) * (static_cast<float>((rand() % 3 + 1)) * speed),
                (rand() % 2 == 0 ? 1 : -1) * (static_cast<float>((rand() % 3 + 1)) * speed)
            },
            .radius = radius,
            .color = {
                static_cast<unsigned char>(rand() % 150 + 105),
                static_cast<unsigned char>(rand() % 150 + 105),
                static_cast<unsigned char>(rand() % 150 + 105),
                255
            }
        };

        if (animationBalls[i].velocity.x < 0.1f || animationBalls[i].velocity.y < 0.1f) {
            i--;
        }
    }
}

void BallAnimation::UpdateSpeedAttributes() {
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

void BallAnimation::Update() {
    for (int i = 0; i < MAX_BALLS; i++) {
        animationBalls[i].position.x += animationBalls[i].velocity.x;
        animationBalls[i].position.y += animationBalls[i].velocity.y;

        if (animationBalls[i].position.x < PADDING || animationBalls[i].position.x > GetScreenWidth() - PADDING)
            animationBalls[i].velocity.x *= -1;

        if (animationBalls[i].position.y < PADDING || animationBalls[i].position.y > GetScreenHeight() - PADDING)
            animationBalls[i].velocity.y *= -1;

        for (int j = i + 1; j < MAX_BALLS; j++) {
            float dx = animationBalls[i].position.x - animationBalls[j].position.x;
            float dy = animationBalls[i].position.y - animationBalls[j].position.y;
            float distance = sqrtf(dx * dx + dy * dy);
            if (distance <= animationBalls[i].radius + animationBalls[j].radius) {
                animationBalls[i].velocity.x *= -1;
                animationBalls[i].velocity.y *= -1;
                animationBalls[j].velocity.x *= -1;
                animationBalls[j].velocity.y *= -1;
            }
        }
    }
}

void BallAnimation::Draw() {
    for (int i = 0; i < MAX_BALLS; i++) {
        float vx = animationBalls[i].velocity.x;
        float vy = animationBalls[i].velocity.y;
        float len = sqrtf(vx * vx + vy * vy);
        float dirX = vx / len;
        float dirY = vy / len;

        for (int j = 1; j <= animationBalls[i].radius * 2; j++) {
            float alpha = (animationBalls[i].radius * 2 - j) / (animationBalls[i].radius * 2);
            Color trailColor = Fade(animationBalls[i].color, alpha * 0.01f);
            Vector2 trailPosition = {
                animationBalls[i].position.x - dirX * animationBalls[i].radius - (vx * j / 5.0f),
                animationBalls[i].position.y - dirY * animationBalls[i].radius - (vy * j / 5.0f)
            };

            float trailRadius = animationBalls[i].radius * 0.5f * (1.0f - j / (animationBalls[i].radius * 2));
            DrawCircleV(trailPosition, trailRadius, trailColor);
        }

        Color ballColor = Fade(animationBalls[i].color, 0.4f);
        DrawCircleV(animationBalls[i].position, animationBalls[i].radius, ballColor);

        Color borderColor = {
            static_cast<unsigned char>(animationBalls[i].color.r * 0.6f),
            static_cast<unsigned char>(animationBalls[i].color.g * 0.6f),
            static_cast<unsigned char>(animationBalls[i].color.b * 0.6f),
            255
        };
        DrawCircleLines(animationBalls[i].position.x, animationBalls[i].position.y, animationBalls[i].radius, borderColor);
    }
}