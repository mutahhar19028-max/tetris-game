#include "icon.h"

Icon::Icon() {
    logoImage.height = IMGAEDATA_HEIGHT;
    logoImage.width = IMGAEDATA_WIDTH;
    logoImage.format = IMGAEDATA_FORMAT;
    logoImage.data = IMGAEDATA_DATA;
    logoImage.mipmaps = 1;
}

Icon::~Icon() {
    UnloadImage(logoImage);
}