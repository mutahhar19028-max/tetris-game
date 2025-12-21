#include "global.h"

// ────────────────────────────────
// Game States
// ────────────────────────────────
bool isPaused = false;
bool isGameOver = false;
bool shouldExit = false;
bool showImages = true;

// ────────────────────────────────
// Game Data
// ────────────────────────────────
std::string player_name = "Player";
GameScreen tempScreen;

// ────────────────────────────────
// Game Dynamics
// ────────────────────────────────
float gameSpeed = 0.6f;

// ────────────────────────────────
// Screen & Layout
// ────────────────────────────────
float screenWidth = 500.0f;
float screenHeight = 620.0f;
float centerX = screenWidth / 2.0f;
float centerY = screenHeight / 2.0f;

const float MENU_WIDTH = 320.0f;
const float MENU_HEIGHT = 290.0f;
const float FONT_SIZE = 45.0f;
const float LINE_HEIGHT = 60.0f;
const float WEIGHT = 5.0f;

const float BUTTON_WIDTH_RATIO = 0.2f;
const int MAX_INPUT_CHARS = 32;

// ────────────────────────────────
// Fonts & Colors
// ────────────────────────────────
const char* gameName = "Tetris";
const char* gameNameFontFile = "assets/fonts/BebasNeue-Regular.ttf";
const char* headingFontFile = "assets/fonts/Poppins-ExtraBold.ttf";
const char* buttonFontFile = "assets/fonts/Poppins-Bold.ttf";
const char* textFontFile = "assets/fonts/Poppins-Regular.ttf";
const char* boosterImg1 = "assets/imgs/tetris.png";
const char* boosterImg2 = "assets/imgs/cursor.png";
const char* mp4Address = "assets/video/loading.mp4";
const char* mp4Address2 = "assets/video/intro-animation.mp4";

int normFontSize = 32;
int titleFontSize = normFontSize + 10;
int gameNameFontSize = titleFontSize + 50;
int buttonFontSize = normFontSize - 8;

const Color HighlightColor = currentTheme.getHeadColor();  // You can change this as needed

// ────────────────────────────────
// Menu
// ────────────────────────────────
int currentOption = 0;

// ────────────────────────────────
// Audio
// ────────────────────────────────
float musicVolume = 1.0f;

// ────────────────────────────────
// Global Object Instances
// ────────────────────────────────
Window window(screenWidth, screenHeight, gameName);
FontManager font;
Audio audio;
GameMenu menu;
AnimationManager animationManager;
Game game;
CursorHighlightEffect cursorHighlight;
BoosterManager boosterManager(500, 100);
BackgroundImage background(screenWidth, screenHeight);
