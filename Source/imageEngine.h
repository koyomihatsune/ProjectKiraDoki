#pragma once

#include <SDL_image.h>
#include <SDL.h>

void imageShow(SDL_Renderer* renderer, const char* imgsource, int posX, int posY);
void blendShow(SDL_Renderer* renderer, const char* imgsource, int posX, int posY, int alpha);
void imageZoomShow(SDL_Renderer* renderer, const char* imgsource, int posX, int posY, int zoomw, int zoomh);