#ifndef THEME_MANAGER_H
#define THEME_MANAGER_H

#include <string>
#include "../../include/raylib/raylib.h"

// Theme struct
struct Theme {
    Color backgroundColor;
    Color boxColor;     // Use alpha < 255 for transparency
    Color normColor;
    Color headColor;

    Theme(Color bg, Color box, Color norm, Color head)
        : backgroundColor(bg), boxColor(box), normColor(norm), headColor(head) {}

    Color getBackgroundColor() const;
    Color getBoxColor() const;
    Color getNormColor() const;
    Color getHeadColor() const;
    void  ChangeIfNeeded(int);
};

extern const int themeCount;
extern int currentThemeIndex;
extern Theme currentTheme;
extern const Theme themes[];
extern const std::string themeNames[];

// Apply the theme to all supported raygui components
void ApplyTheme(const Theme& theme);

// Lighten a color by a given factor (0.0 to 1.0)
Color LightenColor(Color color, float factor);

Color DarkenColor(Color color, float factor);

// Convert Color to uint (used for raygui style)
unsigned int COLOR_TO_UINT(Color color);

// Change to next theme
void CycleTheme();

#endif // THEME_MANAGER_H
