#ifndef CUSTOMCOLORS_H
#define CUSTOMCOLORS_H

#include "../../include/raylib/raylib.h"
#include <vector>

// Custom Colors
extern const Color darkGrey;
extern const Color green;
extern const Color red;
extern const Color orange;
extern const Color yellow;
extern const Color purple;
extern const Color cyan;
extern const Color blue;
extern const Color lightBlue;
extern const Color darkBlue;

std::vector<Color> GetCellColors();

#endif