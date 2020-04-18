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
