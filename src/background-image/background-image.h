#ifndef BACKGROUND_IMAGE_H
#define BACKGROUND_IMAGE_H

#include "../../include/raylib/raylib.h"
#include <vector>
#include <string>

class BackgroundImage {
public:
    BackgroundImage(int screenWidth, int screenHeight);
    ~BackgroundImage();

    void LoadImages();
    void SetImages();
    void Update();           // Call every frame
    void Draw();             // Call every frame
    void NextImage();        // Call on level up

private:
    int screenWidth, screenHeight;
    std::vector<Image> rawImages;
    std::vector<Texture2D> images;
    int currentIndex;
    int nextIndex;

    bool transitioning;
    float transitionAlpha;

    void BeginTransition(int toIndex);
    void EndTransition();
};

#endif // BACKGROUND_IMAGE_H
