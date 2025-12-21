#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS

#include "../../include/raygui/raygui.h" 
#include "game-menu.h"
#include "../core/global.h"
#include "../ui/window-manager.h"
#include "../theme/theme-manager.h"
#include "../animation/animation-manager.h"
#include "../core/game.h"
#include "../ui/cursor-effect.h"


void GameMenu::UpdateMenuScreen() {

    float startX = 0;
    float endX = screenWidth;
    float centerX = (startX + endX) / 2;

    float startY = screenHeight / 3 + 30;
    float buttonWidth = screenWidth / 2.5;
    float buttonHeight = 40 * 1.4;
    float spacing = 15;

    // Calculate centered position for the game title
    int textWidth = MeasureText(gameName, gameNameFontSize);
    Vector2 position = {
        centerX - textWidth / 2 + 64,  // Horizontal center + slight right shift
        startY - 140                   // Vertical offset for style
    };

    // --- EFFECT SETTINGS ---
    float outlineOffset = 2.0f;                        // Outline thickness
    Color outlineColor = currentTheme.getBoxColor();                  // Outline color
    Color baseColor = currentTheme.getHeadColor(); // Main text color
    Color glowColor = Fade(baseColor, 0.3f);     // Soft glow behind text
    float pulse = 0.6f + 0.4f * sin(GetTime() * 2.0f); // Pulsing transparency (0.2 to 1.0)
    Color finalColor = Fade(baseColor, pulse);   // Final text color with pulsing

    // --- OUTLINE EFFECT (draw in 8 directions) ---
    const Vector2 offsets[] = {
        {-outlineOffset,  0}, {outlineOffset,  0},
        {0, -outlineOffset}, {0,  outlineOffset},
        {-outlineOffset, -outlineOffset}, {-outlineOffset, outlineOffset},
        {outlineOffset, -outlineOffset},  {outlineOffset, outlineOffset},
    };
    for (const Vector2& off : offsets) {
        DrawTextEx(font.getbigHeadFont(),
                gameName,
                {position.x + off.x, position.y + off.y},
                gameNameFontSize, 3, outlineColor);
    }

    // --- GLOW EFFECT (draw 3 slightly offset shadows) ---
    for (int i = 1; i <= 3; i++) {
        DrawTextEx(font.getbigHeadFont(),
                gameName,
                {position.x + i, position.y + i},
                gameNameFontSize, 3, glowColor);
    }

    // --- MAIN TEXT (with pulsating transparency) ---
    DrawTextEx(font.getbigHeadFont(),
            gameName,
            position,
            gameNameFontSize, 3, finalColor);


    Rectangle play1Btn     = { centerX - buttonWidth / 2, startY, (float)buttonWidth, (float)buttonHeight };

    startY += buttonHeight + spacing;

    Rectangle play2Btn     = { centerX - buttonWidth / 2, startY, (float)buttonWidth, (float)buttonHeight };

    startY += buttonHeight + spacing;

    Rectangle settingsBtn  = { centerX - buttonWidth / 2, startY, (float)buttonWidth, (float)buttonHeight };

    startY += buttonHeight + spacing;

    Rectangle creditsBtn   = { centerX - buttonWidth / 2, startY, (float)buttonWidth, (float)buttonHeight };

    GuiSetStyle(BUTTON, TEXT_PADDING, 8);         // Horizontal text padding
    GuiSetStyle(BUTTON, BORDER_WIDTH, 2);         // Border thickness
    GuiSetStyle(BUTTON, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);  // Align text

    GuiSetFont(font.getButtonFont());
    GuiSetStyle(DEFAULT, TEXT_SIZE, buttonFontSize);  // 24 is the defualt font size

   if(GuiButton(play1Btn, GuiIconText(ICON_PLAYER_PLAY, "Campaign Mode"))) {
        game.Reset();
        currentScreen = GameScreen::PLAY1;
        return;
    }

    if(GuiButton(play2Btn, GuiIconText(ICON_PLAYER_PLAY, "Endless Mode"))) {
        game.Reset();
        currentScreen = GameScreen::PLAY2;
        return;
    }

    if(GuiButton(settingsBtn, GuiIconText(ICON_GEAR, "Game Settings"))) {
        currentScreen = GameScreen::SETTING;
        return;
    }

    if(GuiButton(creditsBtn, GuiIconText(ICON_FILETYPE_TEXT, "Game Credits"))) {
        currentScreen = GameScreen::CREDITS;
        return;
    }
}

void GameMenu::UpdateSettingsScreen() {

    float startX = 0;
    float endX = screenWidth;
    float centerX = (startX + endX) / 2;

    float startY = screenHeight / 12;

    Vector2 textWidth = MeasureTextEx(font.getHeadFont(), "Settings", titleFontSize, 2);

    DrawTextEx(font.getHeadFont(), "Settings", { centerX - textWidth.x / 2, startY } , titleFontSize, 2, currentTheme.getHeadColor());

    float spacing = 20;
    float selectorY = startY + 3.75 * spacing;
    float buttonSize = 40;

    // === Theme Selector ===

    const char* currentName = themeNames[currentThemeIndex].c_str();
    Vector2 nameWidth = MeasureTextEx(font.getNormFont(), currentName, normFontSize, 2);
    DrawTextEx(font.getNormFont(), currentName, { centerX - nameWidth.x / 2, selectorY }, normFontSize, 2, currentTheme.getNormColor());
    
    float sparse = 80;
    float selectorWidth = nameWidth.x / 2.1 + sparse;

    Rectangle leftArrow  = { (float)( centerX - selectorWidth), selectorY, buttonSize, buttonSize };
    Rectangle rightArrow = { (float)( centerX + selectorWidth - buttonSize ), selectorY, buttonSize, buttonSize };

    if (GuiButton(leftArrow, "<")) {
        currentThemeIndex = (currentThemeIndex - 1 + themeCount) % themeCount;
        currentTheme = themes[currentThemeIndex];
        ApplyTheme(currentTheme);
        cursorHighlight.setColor(currentTheme.getBackgroundColor());
    }
    if (GuiButton(rightArrow, ">")) {
        currentThemeIndex = (currentThemeIndex + 1) % themeCount;
        currentTheme = themes[currentThemeIndex];
        ApplyTheme(currentTheme);
        cursorHighlight.setColor(currentTheme.getBackgroundColor());
    }

    startY = selectorY + buttonSize + 20;
    selectorY = startY;

    // === Music Selector ===

    float width = MeasureTextEx(font.getNormFont(), "Music", normFontSize, 2).x / 2;
    DrawTextEx(font.getNormFont(), "Music", { centerX - width, startY}, normFontSize, 2, currentTheme.getNormColor());
    
    selectorWidth = width / 2 + sparse;

    leftArrow  = { (float)( centerX - selectorWidth), selectorY, buttonSize, buttonSize };
    rightArrow = { (float)( centerX + selectorWidth - buttonSize ), selectorY, buttonSize, buttonSize };

    if (GuiButton(leftArrow, "<")) {
        audio.setPreviousBackgroundMusic();
    }
    if (GuiButton(rightArrow, ">")) {
        audio.setNextBackgroundMusic();
    }

    startY = selectorY + buttonSize + 20;
    selectorY = startY;

    // === Animation Selector ===

    const char* animName = animationManager.animationNames[animationManager.currentAnimationIndex];
    Vector2 animTextSize = MeasureTextEx(font.getNormFont(), animName, normFontSize, 2);
 
    // Draw animation name
    DrawTextEx(font.getNormFont(), animName, { centerX - animTextSize.x / 2, selectorY }, normFontSize, 2, currentTheme.getNormColor());
 
    selectorWidth = animTextSize.x / 3.9 + sparse;
 
    Rectangle animLeftArrow  = { centerX - selectorWidth, selectorY, buttonSize, buttonSize };
    Rectangle animRightArrow = { centerX + selectorWidth - buttonSize, selectorY, buttonSize, buttonSize };
 
    if(GuiButton(animLeftArrow, "<")) {
        animationManager.currentAnimationIndex = (animationManager.currentAnimationIndex - 1 + static_cast<int>(AnimationType::COUNT)) % static_cast<int>(AnimationType::COUNT);
        animationManager.SetAnimation(static_cast<AnimationType>(animationManager.currentAnimationIndex));
    }

    if(GuiButton(animRightArrow, ">")) {
        animationManager.currentAnimationIndex = (animationManager.currentAnimationIndex + 1) % static_cast<int>(AnimationType::COUNT);
        animationManager.SetAnimation(static_cast<AnimationType>(animationManager.currentAnimationIndex));
    }
     
    startY = selectorY + buttonSize + 85;

    // === Volume Slider ===
    float sliderWidth = screenWidth / 3;
    float sliderHeight = 20;

    Rectangle volumeSlider = {
        centerX - sliderWidth / 2,
        startY,
        sliderWidth,
        sliderHeight
    };

    // Label
    DrawTextEx(font.getNormFont(), "Music Volume", { centerX - MeasureTextEx(font.getNormFont(), "Music Volume", normFontSize, 2).x / 2, startY - 50}, normFontSize, 2, currentTheme.getNormColor());
    
    GuiSetStyle(SLIDER, SLIDER_PADDING, 2); 

    int sliderPosition = GuiSliderBar(volumeSlider, "0%", "100%", &musicVolume, 0.0f, 1.0f);

    SetMusicVolume(audio.getBackgroundMusic(), musicVolume);

    // === Cursor Highlight Toggle and Radius ===
    startY += sliderHeight + 25;
    selectorY = startY;

    bool enabled = cursorHighlight.enabled;
    enabled = GuiCheckBox(
        (Rectangle){
            centerX - 70,
            selectorY,
            25, 25
        },
        "Enable Cursor Highlight", &cursorHighlight.enabled);

    if(cursorHighlight.enabled) {
        cursorHighlight.setColor(currentTheme.getBackgroundColor());
        float radius = cursorHighlight.radius;
        float sliderWidth = screenWidth / 3;
        float sliderHeight = 20;

        // Label
        DrawTextEx(font.getNormFont(), "Highlight Radius", 
            { centerX - MeasureTextEx(font.getNormFont(), "Highlight Radius", normFontSize, 2).x / 2, selectorY + 35 }, 
            normFontSize, 2, currentTheme.getNormColor());

        Rectangle radiusSlider = {
            centerX - sliderWidth / 2,
            selectorY + 75,
            sliderWidth,
            sliderHeight
        };

        int sliderPosition2 = GuiSlider(radiusSlider, "1%", "100%", &cursorHighlight.radius, 20.0f, 150.0f);

        startY = selectorY + sliderHeight + 40;
    } else {
        startY = selectorY + 20; 
    }

    // === Back Button ===
    int buttonWidth = screenWidth / 5;
    int buttonHeight = 40;

    startY += sliderHeight + 35;

    Rectangle backBtn = {
        centerX - buttonWidth / 2,
        startY,
        (float)buttonWidth,
        (float)buttonHeight
    };

    if (GuiButton(backBtn, "Back")) {
        currentScreen = MENU;
    }
}
 
void GameMenu::UpdateGameplayScreen() {
    
    float startX = 320;
    float maxLen = 166;
    float endX = startX + maxLen;

    float startY = 40;
    float endY = 570;

    float centerX = (startX + endX) / 2;
    float centerY = (startY + endY) / 2;

    float minHeight = 60;
    float headSize = 32;
    float gap = 35;
    int spacing = 3;

    DrawTextEx(font.getHeadFont(), "Score", {centerX - MeasureTextEx(font.getHeadFont(), "Score", headSize, 3).x / 2, startY}, headSize, spacing, currentTheme.getHeadColor());
    startY += gap;
    DrawRectangleRounded({startX, startY, maxLen, minHeight}, 0.3, 6, currentTheme.getBoxColor());

    char scoreText[10];
    sprintf(scoreText, "%d", game.stats.getScore());
    Vector2 textSize = MeasureTextEx(font.getHeadFont(), scoreText, headSize, 3);
    DrawTextEx(font.getHeadFont(), scoreText, {centerX - textSize.x / 2,  startY + 12}, headSize, 3, currentTheme.getHeadColor());

    startY += minHeight + gap / 2;

    DrawTextEx(font.getHeadFont(), "Next", {centerX - MeasureTextEx(font.getHeadFont(), "Next", headSize, spacing).x / 2, startY}, headSize, spacing, currentTheme.getHeadColor());
    startY += gap;
    DrawRectangleRounded({startX, startY, maxLen, minHeight * (float)1.5 + 30}, 0.3, 6, currentTheme.getBoxColor());
    
    startY += minHeight * 1.5 + gap / 2 + 30;

    DrawTextEx(font.getHeadFont(), "Level", {centerX - MeasureTextEx(font.getHeadFont(), "Level", headSize, spacing).x / 2, startY}, headSize, spacing, currentTheme.getHeadColor());
    startY += gap;
    DrawRectangleRounded({startX, startY, maxLen, minHeight}, 0.3, 6, currentTheme.getBoxColor());

    char levelText[10];
    sprintf(levelText, "%d", game.stats.getCurrentLevel());
    textSize = MeasureTextEx(font.getHeadFont(), levelText, headSize, spacing);
    DrawTextEx(font.getHeadFont(), levelText, {centerX - textSize.x / 2,  startY + 12}, headSize, spacing, currentTheme.getHeadColor());

    startY += minHeight + gap / 2;

    DrawTextEx(font.getHeadFont(), "Lines", {centerX - MeasureTextEx(font.getHeadFont(), "Lines", headSize, spacing).x / 2, startY}, headSize, spacing, currentTheme.getHeadColor());
    startY += gap / 2 + 5;
    DrawTextEx(font.getHeadFont(), "Cleared", {centerX - MeasureTextEx(font.getHeadFont(), "Cleared", headSize, spacing).x / 2, startY}, headSize, spacing, currentTheme.getHeadColor());
    startY += gap / 2 + 15;
    DrawRectangleRounded({startX, startY, maxLen, minHeight}, 0.3, 6, currentTheme.getBoxColor());

    char linesText[10];
    sprintf(linesText, "%d", game.stats.getLinesCleared());
    textSize = MeasureTextEx(font.getHeadFont(), linesText, headSize, spacing);
    DrawTextEx(font.getHeadFont(), linesText, {centerX - textSize.x / 2,  startY + 12}, headSize, spacing, currentTheme.getHeadColor());

    startY += minHeight + gap / 2;

    if(GuiButton({ centerX - 44, startY - 10, maxLen / (float)1.8, minHeight / (float)1.2 }, "Pause")) {
        isPaused = true;
        menu.SetCurrentScreen(PAUSED);
    }
}

void GameMenu::UpdateEndlessScreen() {
    float startX = 320;
    float maxLen = 166;
    float endX = startX + maxLen;

    float startY = 40;
    float endY = 570;

    float centerX = (startX + endX) / 2;
    float centerY = (startY + endY) / 2;

    float minHeight = 60;
    float headSize = 32;
    float gap = 35;
    int spacing = 3;

    DrawTextEx(font.getHeadFont(), "Score", {centerX - MeasureTextEx(font.getHeadFont(), "Score", headSize, 3).x / 2, startY}, headSize, spacing, currentTheme.getHeadColor());
    startY += gap;
    DrawRectangleRounded({startX, startY, maxLen, minHeight}, 0.3, 6, currentTheme.getBoxColor());

    char scoreText[10];
    sprintf(scoreText, "%d", game.stats.getScore());
    Vector2 textSize = MeasureTextEx(font.getHeadFont(), scoreText, headSize, 3);
    DrawTextEx(font.getHeadFont(), scoreText, {centerX - textSize.x / 2,  startY + 12}, headSize, 3, currentTheme.getHeadColor());

    startY += minHeight + gap / 2;

    DrawTextEx(font.getHeadFont(), "Next", {centerX - MeasureTextEx(font.getHeadFont(), "Next", headSize, spacing).x / 2, startY}, headSize, spacing, currentTheme.getHeadColor());
    startY += gap;
    DrawRectangleRounded({startX, startY, maxLen, minHeight * (float)1.5 + 30}, 0.3, 6, currentTheme.getBoxColor());
    
    startY += minHeight * 1.5 + gap / 2 + 30;

    DrawTextEx(font.getHeadFont(), "Time Left", {centerX - MeasureTextEx(font.getHeadFont(), "Time Left", headSize, spacing).x / 2, startY}, headSize, spacing, currentTheme.getHeadColor());
    startY += gap;
    DrawRectangleRounded({startX, startY, maxLen, minHeight}, 0.3, 6, currentTheme.getBoxColor());

    char timeText[10];
    sprintf(timeText, "%d", game.stats.getCurrentLevel()); //
    textSize = MeasureTextEx(font.getHeadFont(), timeText, headSize, spacing);
    DrawTextEx(font.getNormFont(), timeText, {centerX - textSize.x / 2,  startY + 12}, headSize, spacing, currentTheme.getNormColor());

    startY += minHeight + gap / 2;

    DrawTextEx(font.getHeadFont(), "Lines", {centerX - MeasureTextEx(font.getHeadFont(), "Lines", headSize, spacing).x / 2, startY}, headSize, spacing, currentTheme.getHeadColor());
    startY += gap / 2 + 5;
    DrawTextEx(font.getHeadFont(), "Cleared", {centerX - MeasureTextEx(font.getHeadFont(), "Cleared", headSize, spacing).x / 2, startY}, headSize, spacing, currentTheme.getHeadColor());
    startY += gap / 2 + 15;
    DrawRectangleRounded({startX, startY, maxLen, minHeight}, 0.3, 6, currentTheme.getBoxColor());

    char linesText[10];
    sprintf(linesText, "%d", game.stats.getLinesCleared());
    textSize = MeasureTextEx(font.getHeadFont(), linesText, headSize, spacing);
    DrawTextEx(font.getHeadFont(), linesText, {centerX - textSize.x / 2,  startY + 12}, headSize, spacing, currentTheme.getHeadColor());

    startY += minHeight + gap / 2;

    if(GuiButton({ centerX - 44, startY - 10, maxLen / (float)1.8, minHeight / (float)1.2 }, "Pause")) {
        isPaused = true;
        menu.SetCurrentScreen(PAUSED);
    }
}

void GameMenu::UpdateCreditsScreen() {
    float startX = 0;
    float endX = screenWidth;
    float centerX = (startX + endX) / 2;

    float startY = screenHeight / 8;

    Vector2 textWidth = MeasureTextEx(font.getHeadFont(), "Credits", titleFontSize, 2);

    DrawTextEx(font.getHeadFont(), "Credits", { centerX - textWidth.x / 2, startY } , titleFontSize, 2, currentTheme.getHeadColor());

    // Credit lines
    const char* credits[] = {
        "Developed by Muhammad Mutahhar Siddique",
        "A solo project built entirely in C++",
        "Classic Tetris mechanics with modern twists",
        "",
        "Built With:",
        "- C++17 for core logic and systems",
        "- Raylib for graphics and input",
        "- raygui for UI components",
        "- FFmpeg for intro video support",
        ""
    };

    const int creditLineCount = sizeof(credits) / sizeof(credits[0]);
    int textFontSize = 20;

    float lineStartY = startY + 80;
    float lineSpacing = 30.0f;

    for (int i = 0; i < creditLineCount; ++i) {
        int lineWidth = MeasureTextEx(font.getNormFont(), credits[i], textFontSize, 2).x;
        float posX = (screenWidth - lineWidth) / 2.0f;
        float posY = lineStartY + i * lineSpacing;

        DrawTextEx(font.getNormFont(), credits[i], { posX, posY }, textFontSize, 2, currentTheme.getNormColor());
    }


    // Back button
    int buttonWidth = screenWidth / 5;
    int buttonHeight = 40;
    float buttonX = (screenWidth - buttonWidth) / 2;
    float buttonY = screenHeight * 0.75f;

    if (GuiButton({ buttonX, buttonY, (float)buttonWidth, (float)buttonHeight }, "Back")) {
        currentScreen = MENU;
    }
}

void GameMenu::UpdatePauseScreen() {
    // Constants
    constexpr float TITLE_VERTICAL_FRACTION = 0.2f;
    constexpr float BUTTON_WIDTH_RATIO = 0.2f;
    constexpr int BUTTON_HEIGHT = 40;
    constexpr float BUTTON_SPACING = 10.0f;

    const char* title = "Paused";

    // Measure and center title

    Vector2 textWidth = MeasureTextEx(font.getHeadFont(), title, titleFontSize, 2);

    float startY = screenHeight / 8;

    DrawTextEx(font.getHeadFont(), title, { centerX - textWidth.x / 2, startY } , titleFontSize, 2, currentTheme.getHeadColor());


    // Calculate button dimensions and positions
    float buttonWidth = screenWidth * BUTTON_WIDTH_RATIO;
    float buttonX = (screenWidth - buttonWidth) / 2.0f;
    startY = screenHeight * 0.5f;

    Rectangle resumeButton = { buttonX, startY, buttonWidth, (float)BUTTON_HEIGHT };
    Rectangle menuButton = { buttonX, startY + BUTTON_HEIGHT + BUTTON_SPACING, buttonWidth, (float)BUTTON_HEIGHT };

    // Handle button clicks
    if (GuiButton(resumeButton, "Resume")) {
        isPaused = false;
    }

    if (GuiButton(menuButton, "Back")) {
        currentScreen = GameScreen::MENU;
    }
}

void GameMenu::UpdateGameOverScreen() {
    // Constants
    constexpr float TITLE_VERTICAL_FRACTION = 1.0f / 6.0f;
    constexpr float BUTTON_WIDTH_RATIO = 0.2f; // 1/5th of screen width
    constexpr int BUTTON_HEIGHT = 40;
    constexpr float BUTTON_VERTICAL_POSITION_RATIO = 0.75f;

    const char* title = "GAME OVER";

    float startY = screenHeight / 8;

    Vector2 textWidth = MeasureTextEx(font.getHeadFont(), title, titleFontSize, 2);

    DrawTextEx(font.getHeadFont(), title, { centerX - textWidth.x / 2, startY } , titleFontSize, 2, currentTheme.getHeadColor());


    // Restart button
    float buttonWidth = screenWidth * BUTTON_WIDTH_RATIO;
    float buttonX = (screenWidth - buttonWidth) / 2.0f;
    float buttonY = screenHeight * BUTTON_VERTICAL_POSITION_RATIO;

    Rectangle restartButton = { buttonX, buttonY, buttonWidth, (float)BUTTON_HEIGHT };

    if (GuiButton(restartButton, "Restart")) {
        currentScreen = tempScreen;
        game.Reset();
    }
}

void GameMenu::UpdateLevelUpScreen() {
    // Constants
    constexpr int BUTTON_HEIGHT = 40;
    constexpr float BUTTON_VERTICAL_POSITION_RATIO = 0.75f;

    const char* title = "LEVEL UP";

    float startY = screenHeight / 8;

    Vector2 textWidth = MeasureTextEx(font.getHeadFont(), title, titleFontSize, 2);

    DrawTextEx(font.getHeadFont(), title, { centerX - textWidth.x / 2, startY } , titleFontSize, 2, currentTheme.getHeadColor());

    // Restart button
    float buttonWidth = screenWidth * BUTTON_WIDTH_RATIO;
    float buttonX = (screenWidth - buttonWidth) / 2.0f;
    float buttonY = screenHeight * BUTTON_VERTICAL_POSITION_RATIO;

    Rectangle confirmButton = { buttonX, buttonY, buttonWidth, (float)BUTTON_HEIGHT };

    if(GuiButton(confirmButton, "Confirm")) {
        currentScreen = PLAY1;
    }
}
