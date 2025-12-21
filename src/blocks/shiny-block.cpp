#include "shiny-block.h"
#include "../core/global.h"
#include <cmath>   // For sin pulse effect
#include <cstdlib> // For rand()
#include <vector>

ShinyBlock::ShinyBlock() {
    shineDuration = 5.0f;
    shineTimer = 0.0f;
    isShining = true;
    isLocked = false;

    cells[0] = { Position(0,1), Position(1,0), Position(1,1), Position(1,2) };
    cells[1] = { Position(0,1), Position(1,1), Position(2,1), Position(1,2) };
    cells[2] = { Position(1,0), Position(1,1), Position(1,2), Position(2,1) };
    cells[3] = { Position(1,0), Position(0,1), Position(1,1), Position(2,1) };

    Move(0, 3); // Center the block
}

void ShinyBlock::Update(float deltaTime) {
    if (isShining && !isLocked) {
        shineTimer += deltaTime;
        if (shineTimer >= shineDuration) {
            isShining = false;
        }
    }
}

void ShinyBlock::Draw(int offsetX, int offsetY) {
    std::vector<Position> tiles = GetCellPositions();
    Color baseColor = GetCellColors()[getID()];

    for (Position item : tiles) {
        if (isShining) {
            float pulse = (std::sin(GetTime() * 5) + 1.0f) * 0.5f;
            Color glow = {
                (unsigned char)(baseColor.r + pulse * (255 - baseColor.r)),
                (unsigned char)(baseColor.g + pulse * (255 - baseColor.g)),
                (unsigned char)(baseColor.b + pulse * (255 - baseColor.b)),
                255
            };
            DrawRectangle(item.column * 30 + offsetX, item.row * 30 + offsetY, 29, 29, glow);
        } else {
            DrawRectangle(item.column * 30 + offsetX, item.row * 30 + offsetY, 29, 29, baseColor);
        }
    }
}

void ShinyBlock::OnLock() {
    isLocked = true;
    if (isShining) {
        int random = rand() % 2;
        if (random == 0) {
            boosterManager.AddBooster(std::make_shared<ClearLineBooster>(boosterImg1));
        } else {
            boosterManager.AddBooster(std::make_shared<ScoreMultiplierBooster>(boosterImg2, 5.0f));
        }
    }
}

bool ShinyBlock::IsShining() const {
    return isShining;
}
