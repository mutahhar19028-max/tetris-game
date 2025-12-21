#ifndef BOOSTER_H
#define BOOSTER_H

#include "../../include/raylib/raylib.h"

class Booster {
protected:
    Texture2D icon;
    bool active;

public:
    Booster(const char* texturePath);
    virtual ~Booster();

    virtual void Activate() = 0;
    virtual void Update(float) = 0;
    virtual void Deactivate();
    void Draw(int x, int y);

    bool IsActive() const;
};

class ClearLineBooster : public Booster {
public:
    ClearLineBooster(const char* texturePath);
    void Activate() override;
    void Update(float) override;
    void Deactivate() override;
};

class ScoreMultiplierBooster : public Booster {
private:
    float duration;
    float timer;

public:
    ScoreMultiplierBooster(const char* texturePath, float duration);
    void Update(float deltaTime) override;
    void Activate() override;
    void Deactivate() override;
};

#endif // BOOSTER_H
