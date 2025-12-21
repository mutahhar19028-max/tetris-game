#include "menu.h"
#include "../core/global.h"

Menu::Menu() : currentScreen(MENU), currentOption(0) {
    menuX = screenWidth / 2 - MENU_WIDTH / 2;
    menuY = screenHeight / 2 - MENU_HEIGHT / 2;
}

void Menu::SetCurrentScreen(GameScreen screen) { currentScreen = screen; }

GameScreen Menu::GetCurrentScreen() { return currentScreen; }

void Menu::HandleMenu() {
    switch(currentOption) {
        case 0:
            currentScreen = PLAY1;
            break;
        case 1:
            currentScreen = PLAY2;
            break;
        case 3:
            currentOption = 0;
            currentScreen = SETTING;
            break;
    }
}
