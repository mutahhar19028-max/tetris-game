#include <iostream>
#include <thread>
#include <atomic>

#include "../../include/raylib/raylib.h"
#include "../../include/raygui/raygui.h"

#include "../ui/cursor-effect.h"
#include "../util/game-utils.h"

#include "../intro-video/video-player.h"
#include "../intro-video/intro-video.h" 

#include "../util/icon.h"

std::atomic<bool> imagesDone = false;

void LoadImagesAsync() {
    background.LoadImages();
    std::cerr << "~ Images Loaded ~" << std::endl;
    imagesDone = true;
}

int main() {

    Icon icon;
    SetWindowIcon(icon.logoImage);

    std::thread imageThread(LoadImagesAsync);

    IntroVideo loading(mp4Address);
    IntroVideo introVideo(mp4Address2);

    imageThread.join();

    background.SetImages();

    cursorHighlight.setColor(currentTheme.getBackgroundColor());

    ApplyTheme(currentTheme);

    // Main game loop
    while (!WindowShouldClose() && !shouldExit) {

        BeginFrame();

            switch (menu.GetCurrentScreen()) {
                case MENU:
                    menu.UpdateMenuScreen();
                    break;
                case PLAY1:
                    PlayGame(PLAY1, true);
                    break;
                case PLAY2:
                    PlayGame(PLAY2, false);
                    break;
                case LEVELUP:
                    menu.UpdateLevelUpScreen();
                    break;
                case GAMEOVER:
                    menu.UpdateGameOverScreen();
                    break;
                case CREDITS:
                    menu.UpdateCreditsScreen();
                    break;
                case SETTING:
                    menu.UpdateSettingsScreen();
                    break;
                case EXIT:
                    shouldExit = true;
                    break;
            }

        EndFrame();
    }

    CloseWindow();
    return 0;
}
