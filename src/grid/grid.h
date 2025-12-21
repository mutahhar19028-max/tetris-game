#ifndef GRID_H
#define GRID_H

#include "../../include/raylib/raylib.h"
#include <vector>

class Grid {
private:
    void MoveRowDown(int row, int numRows);
    int numRows;
    int numCols;
    int cellSize;
    std::vector<Color> colors;

public:
    int grid[20][10];

    Grid();
    void Initialize();
    void Draw();
    int  GetRows() const;
    int  GetColumns() const;
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int  ClearFullRows();

    bool IsRowFull(int row);
    bool IsRowEmpty(int);
    void ClearRow(int row);
};

#endif // GRID_H