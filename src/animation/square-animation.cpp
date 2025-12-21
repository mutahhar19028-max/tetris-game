#include <cmath>
#include <cstdlib>
#include <ctime>

#include "square-animation.h"
#include "../core/global.h"

#define SQUARE_MAX_SPEED 20.0f

FloatingSquareAnimation::FloatingSquareAnimation() {
    srand(time(NULL));
    for (int i = 0; i < MAX_SQUARES; i++) {
        float size = static_cast<float>(rand() % 30 + 20);
        float speed = SQUARE_MAX_SPEED / size * sp;

        squares[i] = {
            .position = {
                static_cast<float>(rand() % (GetScreenWidth() - 2 * SQUARE_PADDING) + SQUARE_PADDING),
                static_cast<float>(rand() % (GetScreenHeight() - 2 * SQUARE_PADDING) + SQUARE_PADDING)
            },
            .velocity = {
                (rand() % 2 == 0 ? 1 : -1) * (static_cast<float>((rand() % 2 + 1)) * speed),
                (rand() % 2 == 0 ? 1 : -1) * (static_cast<float>((rand() % 2 + 1)) * speed)
            },
            .size = size,
            .rotation = static_cast<float>(rand() % 360),
            .rotationSpeed = (rand() % 2 == 0 ? 1 : -1) * ((float)(rand() % 30) / 10.0f),
            .color = {
                static_cast<unsigned char>(rand() % 150 + 105),
                static_cast<unsigned char>(rand() % 150 + 105),
                static_cast<unsigned char>(rand() % 150 + 105),
                200
            }
        };
    }
}

void FloatingSquareAnimation::UpdateSpeedAttributes() {
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

void FloatingSquareAnimation::Update() {
    for (int i = 0; i < MAX_SQUARES; i++) {
        squares[i].position.x += squares[i].velocity.x;
        squares[i].position.y += squares[i].velocity.y;
        squares[i].rotation += squares[i].rotationSpeed;

        if (squares[i].position.x < SQUARE_PADDING || squares[i].position.x > GetScreenWidth() - SQUARE_PADDING)
            squares[i].velocity.x *= -1;

        if (squares[i].position.y < SQUARE_PADDING || squares[i].position.y > GetScreenHeight() - SQUARE_PADDING)
            squares[i].velocity.y *= -1;
    }
}

void FloatingSquareAnimation::Draw() {
    for (int i = 0; i < MAX_SQUARES; i++) {
        Vector2 center = { squares[i].size / 2, squares[i].size / 2 };

        DrawRectanglePro(
            { squares[i].position.x, squares[i].position.y, squares[i].size, squares[i].size },
            center,
            squares[i].rotation,
            Fade(squares[i].color, 0.6f)
        );

        DrawRectangleLinesEx(
            { squares[i].position.x, squares[i].position.y, squares[i].size, squares[i].size },
            1,
            squares[i].color
        );
    }
}
