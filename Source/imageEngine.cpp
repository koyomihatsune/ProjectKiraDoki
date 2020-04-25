#pragma once

#include <SDL_image.h>
#include <SDL.h>
#include <SDL_thread.h>

void imageShow(SDL_Renderer* renderer, const char* imgsource, int posX, int posY)
{
    SDL_Texture* img = NULL;
    SDL_Rect desRect;
    int w, h;
    img = IMG_LoadTexture(renderer, imgsource);
    SDL_QueryTexture(img, NULL, NULL, &w, &h);

    SDL_Rect texr;
    texr.x = posX;
    texr.y = posY;
    texr.w = w;
    texr.h = h;

    SDL_RenderCopy(renderer, img, NULL, &texr);
    SDL_DestroyTexture(img);

}

void blendShow(SDL_Renderer* renderer, const char* imgsource, int posX, int posY, int alpha)
{
    SDL_Texture* img = NULL;

    SDL_Rect desRect;
    int w, h;
    img = IMG_LoadTexture(renderer, imgsource);

    SDL_SetTextureBlendMode(img, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(img, alpha);
    SDL_QueryTexture(img, NULL, NULL, &w, &h);

    SDL_Rect texr;
    texr.x = posX;
    texr.y = posY;
    texr.w = w;
    texr.h = h;

    SDL_RenderCopy(renderer, img, NULL, &texr);
    SDL_DestroyTexture(img);

}
void imageZoomShow(SDL_Renderer* renderer, const char* imgsource, int posX, int posY, int zoomw, int zoomh)
{
    SDL_Texture* img = NULL;
    SDL_Rect desRect;
    int w, h;
    img = IMG_LoadTexture(renderer, imgsource);
    SDL_QueryTexture(img, NULL, NULL, &w, &h);

    SDL_Rect texr;
    texr.x = posX-(w * ((float)zoomw / 1000) )/2;
    texr.y = posY-(h * ((float)zoomw / 1000) )/2;
    texr.w = w*((float)zoomw/1000);
    texr.h = h*((float)zoomw/1000);

    SDL_RenderCopy(renderer, img, NULL, &texr);
    SDL_DestroyTexture(img);

}