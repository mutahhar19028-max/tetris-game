#include "window-manager.h"
#include "../core/global.h"
#include "../theme/theme-manager.h"

Window::Window(int width, int height, const char* title)
    : windowDragging(false), isMaximized(false), shouldClose(false), 
      screenWidth(width), screenHeight(height), gameTitle(title) {
    
    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    InitWindow(screenWidth, screenHeight, gameTitle);
    SetTargetFPS(60);

    titleBar = {0, 0, (float)screenWidth, titleBarHeight};
    UpdateButtonPositions();

    previousWindowSize = {(float)screenWidth, (float)screenHeight};
    previousWindowPosition = GetWindowPosition();

    iconTexture = LoadTexture("assets/imgs/tetris.png");
}

void Window::toggleShouldExit() { shouldClose = !shouldClose; }

void Window::Update() {

    int currentWidth = GetScreenWidth();
    int currentHeight = GetScreenHeight();
    if (screenWidth != currentWidth || screenHeight != currentHeight) {
        screenWidth = currentWidth;
        screenHeight = currentHeight;
        UpdateButtonPositions();
    }

    if (windowDragging) {
        Vector2 mouse = GetMousePosition();
        SetWindowPosition((int)(mouse.x - windowDragOffset.x), (int)(mouse.y - windowDragOffset.y));
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOver(titleBar)) {
        windowDragging = true;
        windowDragOffset = GetMousePosition();
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        windowDragging = false;
    }

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mouse = GetMousePosition();

        if (IsMouseOver(minimizeButton)) {
            MinimizeWindow();
        } else if (IsMouseOver(maximizeButton)) {
            if (!isMaximized) {
                previousWindowSize = {(float)GetScreenWidth(), (float)GetScreenHeight()};
                previousWindowPosition = GetWindowPosition();
                SetWindowPosition(0, 0);
                SetWindowSize(GetMonitorWidth(0), GetMonitorHeight(0));
            } else {
                SetWindowSize((int)previousWindowSize.x, (int)previousWindowSize.y);
                SetWindowPosition((int)previousWindowPosition.x, (int)previousWindowPosition.y);
            }
            isMaximized = !isMaximized;
        } else if (IsMouseOver(closeButton)) {
            CloseWindow();
        }
    }
}

void Window::Draw() {
    Color bg = currentTheme.getBackgroundColor();
    Color dark = GetDarkenedColor(bg, 0.8f);
    Color hover = GetDarkenedColor(bg, 1.2f);

    DrawRectangleRec(titleBar, dark);

    // Draw the icon in the top-left corner of the title bar
    Rectangle source = { 0, 0, (float)iconTexture.width, (float)iconTexture.height };
    Rectangle dest = { 3.0f, 3.0f, 24.0f, 24.0f };
    Vector2 origin = { 0.0f, 0.0f };

    // Shadowed title
    Vector2 titlePos = {35, 5}; // Shift right to make room for icon
    DrawTextEx(font.getHeadFont(), gameName, {titlePos.x + 1, titlePos.y + 1}, 20, 2, Fade(BLACK, 0.3f));
    DrawTextEx(font.getHeadFont(), gameName, titlePos, 20, 2, currentTheme.getHeadColor());

    struct {
        Rectangle rect;
        const char* label;
    } buttons[] = {
        {minimizeButton, "-"},
        {maximizeButton, "🗖"},
        {closeButton, "X"}
    };

    for (auto& b : buttons) {
        bool hovering = IsMouseOver(b.rect);
        Color btnColor = hovering ? hover : bg;

        DrawRectangleRec({b.rect.x + 1, b.rect.y + 1, b.rect.width, b.rect.height}, Fade(BLACK, 0.2f));
        DrawRectangleRec(b.rect, btnColor);
        DrawRectangleLinesEx(b.rect, 1, Fade(WHITE, 0.2f));
        DrawTextEx(font.getHeadFont(), b.label, {b.rect.x + 7, b.rect.y + 3}, 20, 2, currentTheme.getHeadColor());
    }

    DrawTexturePro(iconTexture, source, dest, origin, 0.0f, currentTheme.getBackgroundColor());
}

// --- Private Utility Methods ---

void Window::UpdateButtonPositions() {
    float screenWidth = (float)GetScreenWidth();
    minimizeButton = {screenWidth - buttonWidth * 3 - buttonGap * 2, 5, buttonWidth, buttonHeight};
    maximizeButton = {screenWidth - buttonWidth * 2 - buttonGap,     5, buttonWidth, buttonHeight};
    closeButton    = {screenWidth - buttonWidth,                    5, buttonWidth, buttonHeight};
}

bool Window::IsMouseOver(Rectangle rect) {
    return CheckCollisionPointRec(GetMousePosition(), rect);
}

Color Window::GetDarkenedColor(Color color, float factor) {
    return (Color){
        (unsigned char)(color.r * factor),
        (unsigned char)(color.g * factor),
        (unsigned char)(color.b * factor),
        color.a
    };
}

Window::~Window() {
    UnloadTexture(iconTexture);
    CloseWindow();
}
