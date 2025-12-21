#include "background-image.h"
#include "../core/global.h"
#include "../theme/theme-manager.h"
#include <cstdio>

BackgroundImage::BackgroundImage(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
      currentIndex(0), nextIndex(0),
      transitioning(false), transitionAlpha(0.0f)
{}

BackgroundImage::~BackgroundImage() {
    for (auto& img : images) {
        UnloadTexture(img);
    }
}

void BackgroundImage::LoadImages() {
    for(int i = 1; i <= 43; i++) {
        char path[64];
        sprintf(path, "assets/imgs/background-images/%d.jpg", i);
        Image img = LoadImage(path);  // Only this is usually safe-ish; better to use raw I/O
        ImageResize(&img, screenWidth, screenHeight);
        rawImages.push_back(img);
    }
}

void BackgroundImage::SetImages() {
    for (Image& img : rawImages) {
        Texture2D tex = LoadTextureFromImage(img); // Must be in main thread
        UnloadImage(img);
        background.images.push_back(tex);
    }
}

void BackgroundImage::BeginTransition(int toIndex) {
    transitioning = true;
    nextIndex = toIndex % images.size();
    transitionAlpha = 0.0f;
}

void BackgroundImage::NextImage() {
    BeginTransition((currentIndex + 1) % images.size());
    currentTheme.ChangeIfNeeded(currentIndex);
}

void BackgroundImage::Update() {
    if (transitioning) {
        transitionAlpha += 0.02f;
        if (transitionAlpha >= 1.0f) {
            EndTransition();
        }
    }
}

void BackgroundImage::Draw() {
    if (!images.empty()) {
        DrawTexture(images[currentIndex], 0, window.titleBarHeight, WHITE);

        if (transitioning) {
            // Fade in next image over the current one
            DrawTexture(images[nextIndex], 0, window.titleBarHeight, Fade(WHITE, transitionAlpha));
        }

        // Optional: add blur-like overlay (mild transparency for stylistic blur)
        DrawRectangle(0, window.titleBarHeight, screenWidth, screenHeight, Fade(BLACK, 0.2f));
    }
}

void BackgroundImage::EndTransition() {
    currentIndex = nextIndex;
    transitioning = false;
    transitionAlpha = 0.0f;
}
