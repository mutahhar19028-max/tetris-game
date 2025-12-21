#ifndef CURSOR_HIGHLIGHT_EFFECT_H
#define CURSOR_HIGHLIGHT_EFFECT_H

#include "../../include/raylib/raylib.h"

class CursorHighlightEffect {
private:
    Color highlightColor;
    bool softBlur;       // Toggle for soft blur
    float blurStep;      // Controls smoothness of blur

public:
    CursorHighlightEffect();

    bool enabled;
    float radius;

    void Update();
    void Draw() const;
    void setColor(Color color);
    void setSoftBlur(bool enabled); // NEW
    void setBlurStep(float step);   // NEW
};

#endif // CURSOR_HIGHLIGHT_EFFECT_H
