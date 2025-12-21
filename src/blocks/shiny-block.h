#ifndef SHINY_BLOCK_H
#define SHINY_BLOCK_H

#include "block.h"

class ShinyBlock : public Block {
private:
    float shineDuration;    
    float shineTimer;
    bool isShining;
    bool isLocked;

public:
    ShinyBlock();
    void Update(float deltaTime);
    void Draw(int offsetX, int offsetY) override;
    void OnLock();
    bool IsShining() const;
};

#endif // SHINY_BLOCK_H
