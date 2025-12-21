#ifndef GAME_H
#define GAME_H

#include "../grid/grid.h"
#include "../stats/stats-manager.h"
#include "../blocks/blocks.cpp"

class Game {
private:
    Block* nextBlock;
    Block* currentBlock;
    std::vector<Block*> blocks;
    Grid grid;

    void LockBlock();
    bool BlockFits();
    void RotateBlock();
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    Block* GetRandomBlock();
    std::vector<Block*> GetAllBlocks();
    void UpdateScore(int, int);

public:
    StatsManager stats;

    Game();

    void Draw();
    void HandleInput();
    void MoveBlockDown();
    void PlaceDownBlock();
    void EmptyLastRow();
    void Reset();

    ~Game();
};

#endif // GAME_H