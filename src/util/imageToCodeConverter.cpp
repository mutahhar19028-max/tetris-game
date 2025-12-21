#include "../../include/raylib/raylib.h"

int main ()
{
	Image img = LoadImage("../imgs/tetris.png");
	ExportImageAsCode(img, "imageData.h");
	UnloadImage(img);
}