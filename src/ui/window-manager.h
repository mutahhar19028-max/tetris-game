#ifndef WINDOW_SETUP_H
#define WINDOW_SETUP_H

#include "../../include/raylib/raylib.h"

class Window {
public:

    const float titleBarHeight = 30;

    Window(int width, int height, const char* title);

    void toggleShouldExit();

    void Update();
    void Draw();
    
    ~Window();

private:
    Texture2D iconTexture;

    Rectangle titleBar;
    Rectangle minimizeButton, maximizeButton, closeButton;
    Vector2 windowDragOffset;
    Vector2 previousWindowSize, previousWindowPosition;
    bool windowDragging;
    bool isMaximized;
    bool shouldClose;

    // Constants
    const float buttonWidth = 25;
    const float buttonHeight = 20;
    const float buttonGap = 5;

    // Title and dimensions
    int screenWidth;
    int screenHeight;
    const char* gameTitle;

    // Internal utilities
    void UpdateButtonPositions();
    bool IsMouseOver(Rectangle rect);
    Color GetDarkenedColor(Color color, float factor);
};

#endif // WINDOW_SETUP_H
