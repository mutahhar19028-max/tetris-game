#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include "../../include/raylib/raylib.h"

class FontManager {
private:
    Font bigHeadFont;
    Font headFont;
    Font normFont;
    Font buttonFont;

public:

    FontManager();

    Font getbigHeadFont() const;
    Font getHeadFont() const;
    Font getNormFont() const;
    Font getButtonFont() const;
    
    ~FontManager();
};

#endif