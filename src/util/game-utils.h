#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "../core/global.h"
#include "../animation/animation-manager.h"
#include "../ui/window-manager.h"
#include "../theme/theme-manager.h"
#include "../audio/audio-manager.h"

// Constants for boundary settings
constexpr float BOUNDARY_TOP_OFFSET = 27.5f;
constexpr int BOUNDARY_THICKNESS = 7;

void DrawBoundary();
bool EventTriggered(double interval);
void BeginFrame();
void EndFrame();
void PlayGame(GameScreen mode, bool useBoosters);

#endif // GAME_UTILS_H
