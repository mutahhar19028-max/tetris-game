#include "booster.h"
#include "../theme/theme-manager.h"
#include "../core/game.h"
#include "../core/global.h"

Booster::Booster(const char* texturePath) : active(false) { icon = LoadTexture(texturePath); }

Booster::~Booster() { UnloadTexture(icon); }

void Booster::Deactivate() { active = false; }

void Booster::Draw(int x, int y) { DrawTexture(icon, x, y, currentTheme.getBoxColor()); }

bool Booster::IsActive() const { return active; }

// --- ClearLineBooster ---

ClearLineBooster::ClearLineBooster(const char* texturePath) : Booster(texturePath) {}

void ClearLineBooster::Activate() {
    active = true;
    game.EmptyLastRow();
    game.stats.increaseLinesCleared(1);
    game.stats.addScore(100);
    Deactivate();
}

void ClearLineBooster::Update(float) {}

void ClearLineBooster::Deactivate() { active = false; }

// --- ScoreMultiplierBooster ---

ScoreMultiplierBooster::ScoreMultiplierBooster(const char* texturePath, float duration)
    : Booster(texturePath), duration(duration), timer(0.0f) {}

void ScoreMultiplierBooster::Activate() {
    active = true;
    game.stats.scoreMult *= 2;
}

void ScoreMultiplierBooster::Update(float deltaTime) {
    if(active) {
        timer += deltaTime;
        if (timer >= duration)
            Deactivate();
    }
}

void ScoreMultiplierBooster::Deactivate() {
    active = false;
    game.stats.scoreMult *= 2;
}