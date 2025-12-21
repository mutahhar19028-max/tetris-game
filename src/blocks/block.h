#ifndef BLOCK_H
#define BLOCK_H

#include "../../include/raylib/raylib.h"
#include "position.h"
#include "../ui/custom-colors.h"
#include <vector>
#include <map>

class Block {
private:
    int id;
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;

public: 
    Block();
    void Draw(int offsetX, int offsetY);
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    int getID();
    void setID(int id);
    std::map<int, std::vector<Position>> cells;
};

#endif // BLOCK_H