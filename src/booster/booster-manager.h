#ifndef BOOSTER_MANAGER_H
#define BOOSTER_MANAGER_H

#include "booster.h"
#include <vector>
#include <memory>

class BoosterManager {
private:
    std::vector<std::shared_ptr<Booster>> boosters;
    int drawStartX, drawStartY;
    int spacing;

public:
    BoosterManager(int startX, int startY, int spacing = 60);

    void AddBooster(std::shared_ptr<Booster> booster);
    void Update(float deltaTime);
    void Draw();

    void ActivateBooster();
    const std::vector<std::shared_ptr<Booster>>& GetBoosters() const;

    void removeAll();
};

#endif // BOOSTER_MANAGER_H
