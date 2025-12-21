#ifndef GAMEMENU_H
#define GAMEMENU_H

#include "menu.h"

class GameMenu : public Menu {
public:
    void UpdateMenuScreen();
    void UpdateSettingsScreen();
    void UpdateGameplayScreen();
    void UpdateEndlessScreen();
    void UpdatePauseScreen();
    void UpdateCreditsScreen();
    void UpdateLevelUpScreen();
    void UpdateGameOverScreen();
};

#endif
