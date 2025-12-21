#include "position.h"

Position::Position(int row = 0, int column = 0) : row(row), column(column) {}
    
void Position::setPosition(int newRow, int newColumn) {
    row = newRow;
    column = newColumn;
}
    
bool Position::operator==(const Position& other) const { return row == other.row && column == other.column; }
    
bool Position::operator!=(const Position& other) const { return !(*this == other); }
