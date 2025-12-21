#ifndef MENU_H
#define MENU_H

enum GameScreen {
    MENU,
    PLAY1, // leveling mode
    PLAY2, // endless mode
    CREDITS,
    PAUSED,
    GAMEOVER,
    LEVELUP,
    SETTING,
    AUDIO_SETTING,
    THEME_SETTING,
    EXIT
};

class Menu {
private:
    float menuX;
    float menuY;
    int currentOption;

protected:
    GameScreen currentScreen;

public:
    Menu();

    void HandleInput();
    void HandleMenu();

    GameScreen GetCurrentScreen();
    void SetCurrentScreen(GameScreen screen);
};

#endif