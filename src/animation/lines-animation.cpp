#include "lines-animation.h"

WavyLinesAnimation::WavyLinesAnimation() {
    srand(time(NULL));
    timee = 0.0f;

    for(int i = 0; i < MAX_WAVY_LINES; i++) {
        lines[i] = {
            .baseY = (float)(i * (GetScreenHeight() / MAX_WAVY_LINES)),
            .amplitude = (float)(rand() % 20 + 10),  // 10–30 px
            .frequency = ((float)(rand() % 100 + 50)) / 10000.0f,  // 0.005–0.015
            .phase = (float)(rand() % 360) * DEG2RAD,
            .color = {
                (unsigned char)(rand() % 150 + 105),
                (unsigned char)(rand() % 150 + 105),
                (unsigned char)(rand() % 150 + 105),
                255
            }
        };
    }
}

void WavyLinesAnimation::UpdateSpeedAttributes() {
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


void WavyLinesAnimation::Update() {
    timee += GetFrameTime();
}

void WavyLinesAnimation::Draw() {
    for (int i = 0; i < MAX_WAVY_LINES; i++) {
        BeginBlendMode(BLEND_ALPHA);
        for (int x = 0; x < GetScreenWidth(); x += 5) {
            float y = lines[i].baseY + sinf(x * lines[i].frequency + lines[i].phase + timee) * lines[i].amplitude;
            DrawCircle(x, (int)y, 1.5f, Fade(lines[i].color, 0.4f));
        }
        EndBlendMode();
    }
}
