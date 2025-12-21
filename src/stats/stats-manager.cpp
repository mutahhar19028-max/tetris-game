#include "stats-manager.h"
#include "../core/global.h"
#include "../theme/theme-manager.h"
#include "../menu/menu.h"
#include "../../include/raygui/raygui.h"

int StatsManager::linesPerLevel = 10;
float StatsManager::scoreMult = 1.0f;

StatsManager::StatsManager() : level(1), linesCleared(0) {}

int StatsManager::getScore() const { return score; }

int StatsManager::getCurrentLevel() const { return level; }

int StatsManager::getLinesCleared() const { return linesCleared; }

float StatsManager::getGameSpeed() const { return baseSpeed;}

void StatsManager::addScore(int score) { this->score += score * scoreMult; }

void StatsManager::increaseLinesCleared(int lines) { 
    linesCleared += lines;
    if(!(linesCleared < linesPerLevel)) 
        levelUp();
 }

void StatsManager::levelUp() {
    level++;
    linesCleared = 0;

    gameSpeed /= 1.05;

    linesPerLevel += (level % 5) ? 2 : 0;

    menu.SetCurrentScreen(GameScreen::LEVELUP);
}

void StatsManager::reset() {
    score = 0;
    level = 1;
    linesCleared = 0;
}

// 500 width
// 620 height