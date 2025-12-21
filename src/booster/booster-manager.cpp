#include "booster-manager.h"

BoosterManager::BoosterManager(int startX, int startY, int spacing)
    : drawStartX(startX), drawStartY(startY), spacing(spacing) {}

void BoosterManager::AddBooster(std::shared_ptr<Booster> booster) {
    boosters.push_back(booster);
    BoosterManager::ActivateBooster();
}

void BoosterManager::Update(float deltaTime) {
    for (auto& booster : boosters) {
            booster->Update(deltaTime);
    }
}

void BoosterManager::Draw() {
    int yOffset = 0;
    for (const auto& booster : boosters) {
        booster->Draw(drawStartX, drawStartY + yOffset);
        yOffset += spacing;
    }
}

void BoosterManager::ActivateBooster() {
    boosters.back()->Activate();
}

const std::vector<std::shared_ptr<Booster>>& BoosterManager::GetBoosters() const {
    return boosters;
}

void BoosterManager::removeAll() {
    boosters.clear();
}
