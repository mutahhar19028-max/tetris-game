#include "game-utils.h"

float lastUpdateTime = 0.0f;

// Function to handle the start of each frame, clearing background and drawing necessary elements
void BeginFrame() {
    
    ClearBackground(currentTheme.getBackgroundColor());

    if(showImages) {
        background.Update();
        background.Draw();
    } else {
        animationManager.Update();
        animationManager.Draw();
    }

    DrawBoundary();

    window.Update();
    window.Draw();

    cursorHighlight.Update();
    cursorHighlight.Draw();
    
}
// Funtion to end each frame
void EndFrame() {
    EndDrawing();
    UpdateMusicStream(audio.getBackgroundMusic());
}
// Checks if the event is triggered based on time intervals
bool EventTriggered(double interval) {
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
// Draws the boundary around the game area
void DrawBoundary() {
    constexpr float TOP_MARGIN_FACTOR = 2.75f;

    float left = 0.0f;
    float right = screenWidth;
    float top = 10 * TOP_MARGIN_FACTOR;
    float bottom = screenHeight;

    DrawRectangleLinesEx((Rectangle){left, top, right - left, bottom - top}, BOUNDARY_THICKNESS, currentTheme.getBoxColor());
}
// Main game loop for both campaign and endless modes
void PlayGame(GameScreen mode, bool useBoosters) {
    while (!WindowShouldClose() &&
          (menu.GetCurrentScreen() == mode || menu.GetCurrentScreen() == PAUSED) &&
          !shouldExit) {

        UpdateMusicStream(audio.getBackgroundMusic());

        BeginFrame();

        if (menu.GetCurrentScreen() == GAMEOVER) {
            isGameOver ? menu.UpdateGameOverScreen() : menu.SetCurrentScreen(mode);
        }
        else if (menu.GetCurrentScreen() == PAUSED) {
            isPaused ? menu.UpdatePauseScreen() : menu.SetCurrentScreen(mode);
        }
        else {
            game.HandleInput();
            game.Draw();

            if (useBoosters && !boosterManager.GetBoosters().empty()) {
                boosterManager.Update(GetFrameTime());
                boosterManager.Draw();
            }

            if (EventTriggered(gameSpeed))
                game.MoveBlockDown();
        }

        EndDrawing();
    }
}
