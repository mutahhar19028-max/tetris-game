#include "cursor-effect.h"
#include "../theme/theme-manager.h"

CursorHighlightEffect::CursorHighlightEffect()
    : enabled(true), radius(60.0f), highlightColor({255, 255, 255, 60}),
      softBlur(true), blurStep(4.0f) {}

void CursorHighlightEffect::setColor(Color color) {
    highlightColor = color;
    highlightColor.a = 60; // Set base alpha
}

void CursorHighlightEffect::setSoftBlur(bool enabled) { softBlur = enabled; }

void CursorHighlightEffect::setBlurStep(float step) { blurStep = step; }

void CursorHighlightEffect::Update() {
    highlightColor = WHITE;
    highlightColor.a = 60; // Maintain soft alpha
}

void CursorHighlightEffect::Draw() const {
    if (!enabled) return;

    Vector2 mousePos = GetMousePosition();
    float step = softBlur ? blurStep : 10.0f;

    for (float i = radius; i > 0; i -= step) {
        float alpha = (float)(radius - i) / radius * highlightColor.a;
        DrawCircleV(mousePos, i, Color{
            highlightColor.r,
            highlightColor.g,
            highlightColor.b,
            (unsigned char)alpha
        });
    }
}
