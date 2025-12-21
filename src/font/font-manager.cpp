#include "font-manager.h"
#include "../core/global.h"

FontManager::FontManager() {
    headFont = LoadFontEx(headingFontFile, titleFontSize, 0, 0);
    normFont = LoadFontEx(textFontFile, normFontSize, 0, 0);
    bigHeadFont = LoadFontEx(gameNameFontFile, gameNameFontSize, 0, 0);
    buttonFont = LoadFontEx(buttonFontFile, 80, 0, 0);
}

Font FontManager::getbigHeadFont() const { return bigHeadFont; }

Font FontManager::getHeadFont() const { return headFont; }

Font FontManager::getNormFont() const { return normFont; }

Font FontManager::getButtonFont() const { return buttonFont; }

FontManager::~FontManager() {
    UnloadFont(bigHeadFont);
    UnloadFont(headFont);
    UnloadFont(buttonFont);
    UnloadFont(normFont);
}