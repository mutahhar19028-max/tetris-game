#include "../../include/raygui/raygui.h"
#include "../../include/raylib/raymath.h"
#include "../core/global.h"
#include "../theme/theme-manager.h"
#include "../ui/custom-colors.h"

Color Theme::getBackgroundColor() const { return backgroundColor; }
Color Theme::getHeadColor() const { return headColor; }
Color Theme::getNormColor() const { return normColor; }
Color Theme::getBoxColor() const { return boxColor; }

const Theme LightTheme = {
    RAYWHITE,     // backgroundColor
    LIGHTGRAY,    // boxColor
    DARKGRAY,     // textColor
    DARKBLUE      // headTextColor
};

const Theme ForestTheme = {
    (Color){34, 45, 40, 255},    // backgroundColor
    (Color){67, 106, 93, 128},   // boxColor
    (Color){200, 255, 200, 255}, // textColor
    (Color){134, 219, 167, 255}  // headTextColor
};

const Theme MidnightTheme = {
    (Color){20, 24, 82, 255},    // backgroundColor
    (Color){40, 60, 140, 128},   // boxColor
    (Color){180, 200, 255, 255}, // textColor
    (Color){100, 180, 255, 255}  // headTextColor
};

const Theme OceanTheme = {
    (Color){0, 48, 73, 255},     // backgroundColor
    (Color){0, 168, 150, 128},   // boxColor
    (Color){239, 249, 247, 255}, // textColor
    (Color){3, 252, 240, 255}    // headTextColor
};

const Theme EarthyTheme = {
    (Color){51, 42, 34, 255},    // backgroundColor (Dark Brown)
    (Color){111, 78, 55, 128},   // boxColor
    (Color){221, 193, 150, 255}, // textColor
    (Color){255, 236, 179, 255}  // headTextColor
};

const Theme SunsetTheme = {
    (Color){255, 94, 77, 255},   // backgroundColor
    (Color){255, 149, 128, 128}, // boxColor
    (Color){90, 50, 50, 255},    // textColor
    (Color){255, 255, 255, 255}  // headTextColor
};

const Theme NeonTheme = {
    BLACK,                       // backgroundColor
    (Color){10, 255, 200, 128},  // boxColor
    (Color){255, 0, 255, 255},   // textColor
    (Color){255, 255, 0, 255}    // headTextColor
};

const Theme CyberpunkTheme = {
    (Color){15, 15, 15, 255},    // backgroundColor
    (Color){255, 20, 147, 128},  // boxColor (DeepPink)
    (Color){0, 255, 255, 255},   // textColor (Cyan)
    (Color){255, 255, 0, 255}    // headTextColor (Yellow)
};

const Theme RetroTheme = {
    (Color){250, 240, 202, 255}, // backgroundColor
    (Color){195, 90, 80, 128},   // boxColor
    (Color){33, 30, 60, 255},    // textColor
    (Color){120, 180, 110, 255}  // headTextColor
};

const Theme WinterTheme = {
    (Color){230, 240, 255, 255}, // backgroundColor
    (Color){190, 220, 255, 128}, // boxColor
    (Color){80, 100, 140, 255},  // textColor
    (Color){60, 90, 160, 255}    // headTextColor
};

const Theme TerminalTheme = {
    BLACK,                       // backgroundColor
    (Color){0, 255, 0, 128},     // boxColor
    (Color){0, 255, 0, 255},     // textColor
    (Color){0, 200, 0, 255}      // headTextColor
};

const Theme BloodMoonTheme = {
    (Color){50, 0, 0, 255},      // backgroundColor
    (Color){140, 0, 0, 128},     // boxColor
    (Color){250, 100, 100, 255}, // textColor
    (Color){255, 30, 30, 255}    // headTextColor
};

const Theme LavenderTheme = {
    (Color){230, 230, 250, 255}, // backgroundColor
    (Color){216, 191, 216, 128}, // boxColor
    (Color){123, 104, 238, 255}, // textColor
    (Color){147, 112, 219, 255}  // headTextColor
};

const Theme FireTheme = {
    (Color){30, 10, 5, 255},     // backgroundColor
    (Color){200, 60, 0, 128},    // boxColor
    (Color){255, 180, 0, 255},   // textColor
    (Color){255, 80, 0, 255}     // headTextColor
};

const Theme themes[] = {
    ForestTheme, // 1-8
    EarthyTheme, // 9-14
    MidnightTheme, // 15-20
    SunsetTheme, // 21-24
    WinterTheme, // 25 ---
    OceanTheme, 
    RetroTheme,
    BloodMoonTheme,
    LavenderTheme,
    FireTheme
};

const std::string themeNames[] = {
    "Forest",
    "Earthy",
    "Midnight",
    "Sunset",
    "Winter",
    "Ocean",
    "Retro",
    "Blood Moon",
    "Lavender",
    "Fire"
};

const int themeCount = sizeof(themes) / sizeof(themes[0]);
int currentThemeIndex = 0;
Theme currentTheme = themes[0];

void Theme::ChangeIfNeeded(int index) {
    if(index < 9) {
        ApplyTheme(ForestTheme);
        currentThemeIndex = 0;
    }
    else if(index < 15) {
        ApplyTheme(EarthyTheme);
        currentThemeIndex = 1;
    }
    else if(index < 21) {
        ApplyTheme(MidnightTheme);
        currentThemeIndex = 2;
    }   
    else if(index < 25) {
        ApplyTheme(SunsetTheme);
        currentThemeIndex = 3;
    }  
    else {
        ApplyTheme(WinterTheme);
        currentThemeIndex = 4;
    }

    currentTheme = themes[currentThemeIndex];
}


Color LightenColor(Color color, float factor) {
    Color result = color;
    result.r = (unsigned char)(color.r + (255 - color.r) * factor);
    result.g = (unsigned char)(color.g + (255 - color.g) * factor);
    result.b = (unsigned char)(color.b + (255 - color.b) * factor);
    return result;
}

Color DarkenColor(Color color, float factor) {
    Color result = color;
    result.r = (unsigned char)(color.r * (1 - factor));
    result.g = (unsigned char)(color.g * (1 - factor));
    result.b = (unsigned char)(color.b * (1 - factor));
    return result;
}

unsigned int COLOR_TO_UINT(Color color) {
    return ((unsigned int)color.r << 24) |
           ((unsigned int)color.g << 16) |
           ((unsigned int)color.b << 8) |
           (unsigned int)color.a;
}

void ApplyTheme(const Theme& theme) {
    // Box colors
    Color boxNormal    = theme.getBoxColor();
    Color boxFocused   = LightenColor(boxNormal, 0.2f);
    Color borderNormal = LightenColor(theme.getNormColor(), 0.1f);
    Color borderFocus  = LightenColor(theme.getHeadColor(), 0.2f);
    Color textNormal   = theme.getHeadColor();
    Color textFocused  = LightenColor(theme.getHeadColor(), 0.15f);

    // Glossy effect
    Color topGloss = LightenColor(boxNormal, 0.3f);  // Glossy top color (lightens the box color)
    Color bottomGloss = DarkenColor(boxNormal, 0.2f); // Glossy bottom (darkens the box color)

    // BUTTON
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt(topGloss));   // Glossy gradient background
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt(boxFocused)); // Focused state background
    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(textNormal));  // Text color for normal state
    GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(textFocused)); // Text color for focused state
    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, ColorToInt(borderNormal)); // Border color normal
    GuiSetStyle(BUTTON, BORDER_COLOR_FOCUSED, ColorToInt(borderFocus)); // Border color focused

    // SLIDER
    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, ColorToInt(topGloss));
    GuiSetStyle(SLIDER, BASE_COLOR_FOCUSED, ColorToInt(boxFocused));
    GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL, ColorToInt(borderNormal));
    GuiSetStyle(SLIDER, BORDER_COLOR_FOCUSED, ColorToInt(borderFocus));
    GuiSetStyle(SLIDER, TEXT_COLOR_NORMAL, ColorToInt(textNormal));
    GuiSetStyle(SLIDER, TEXT_COLOR_FOCUSED, ColorToInt(textFocused));

    // CHECKBOX
    GuiSetStyle(CHECKBOX, BASE_COLOR_NORMAL, ColorToInt(topGloss));
    GuiSetStyle(CHECKBOX, BASE_COLOR_FOCUSED, ColorToInt(boxFocused));
    GuiSetStyle(CHECKBOX, BORDER_COLOR_NORMAL, ColorToInt(borderNormal));
    GuiSetStyle(CHECKBOX, BORDER_COLOR_FOCUSED, ColorToInt(borderFocus));
    GuiSetStyle(CHECKBOX, TEXT_COLOR_NORMAL, ColorToInt(textNormal));
    GuiSetStyle(CHECKBOX, TEXT_COLOR_FOCUSED, ColorToInt(textFocused));

}

// Function to cycle through themes
void CycleTheme() {
    currentThemeIndex = (currentThemeIndex + 1) % themeCount;
    currentTheme = themes[currentThemeIndex];
    ApplyTheme(currentTheme);
}
