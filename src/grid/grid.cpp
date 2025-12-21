#include "grid.h"
#include "../ui/custom-colors.h"

void Grid::Initialize() {
    for (int row = 0; row < numRows; row++)
        for (int column = 0; column < numCols; column++)
            grid[row][column] = 0;
}

Grid::Grid() {
    numRows = 19;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
}

int Grid::GetRows() const { return numRows; }

int Grid::GetColumns() const { return numCols; }

void Grid::Draw() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            int cellValue = grid[row][column];
            DrawRectangle(column * cellSize + 11, row * cellSize + 11 + cellSize, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int column) { return !(row >= 0 && row < numRows && column >= 0 && column < numCols); }

bool Grid::IsCellEmpty(int row, int column) {
    return !grid[row][column];
}

int Grid::ClearFullRows() {
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--) {
        if (IsRowFull(row)) {
            ClearRow(row);
            completed++;
        } else if (completed > 0) {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row) {
    for (int column = 0; column < numCols; column++)
        if(!grid[row][column])
            return false;
    return true;
}

bool Grid::IsRowEmpty(int row) {
    for (int column = 0; column < numCols; column++)
        if(grid[row][column])
            return false;
    return true;
}

void Grid::ClearRow(int row) {
    for (int column = 0; column < numCols; column++)
        grid[row][column] = 0;
}

void Grid::MoveRowDown(int row, int numRows) {
    for (int column = 0; column < numCols; column++) {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}
