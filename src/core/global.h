#ifndef GLOBAL_H
#define GLOBAL_H

#include "../../include/raylib/raylib.h"

#include "game.h"
#include "../menu/game-menu.h"
#include "../ui/cursor-effect.h"
#include "../audio/audio-manager.h"
#include "../font/font-manager.h"
#include "../ui/window-manager.h"
#include "../animation/animation-manager.h"
#include "../booster/booster-manager.h"
#include "../background-image/background-image.h"
#include  "../theme/theme-manager.h"

#include <string>

// ────────────────────────────────
// Game States
// ────────────────────────────────
extern bool isPaused;
extern bool isGameOver;
extern bool shouldExit;
extern bool showImages;

// ────────────────────────────────
// Game Data
// ────────────────────────────────
extern std::string player_name;
extern GameScreen tempScreen;
// ────────────────────────────────
// Game Dynamics
// ────────────────────────────────
extern float gameSpeed;

// ────────────────────────────────
// Screen & Layout
// ────────────────────────────────
extern float screenWidth;
extern float screenHeight;
extern float centerX;
extern float centerY;

extern const float MENU_WIDTH;
extern const float MENU_HEIGHT;
extern const float FONT_SIZE;
extern const float LINE_HEIGHT;
extern const float WEIGHT;

extern const float BUTTON_WIDTH_RATIO;
extern const int MAX_INPUT_CHARS;

// ────────────────────────────────
// Fonts & Colors
// ────────────────────────────────
extern const char* gameName;
extern const char* gameNameFontFile;
extern const char* headingFontFile;
extern const char* buttonFontFile;
extern const char* textFontFile;
extern const char* boosterImg1;
extern const char* boosterImg2; 
extern const char* mp4Address;
extern const char* mp4Address2;

extern int gameNameFontSize;
extern int titleFontSize;
extern int normFontSize;
extern int buttonFontSize;
extern const Color HighlightColor;

// ────────────────────────────────
// Menu
// ────────────────────────────────
extern const char* options[];
extern int currentOption;

// ────────────────────────────────
// Audio
// ────────────────────────────────
extern float musicVolume;

// ────────────────────────────────
// Global Objects
// ────────────────────────────────
extern Window window;
extern Audio audio;
extern FontManager font;
extern GameMenu menu;
extern Game game;
extern AnimationManager animationManager;
extern CursorHighlightEffect cursorHighlight;
extern BoosterManager boosterManager;
extern BackgroundImage background;

// ────────────────────────────────
// Game Dynamics
// ────────────────────────────────


#endif // GLOBAL_H
