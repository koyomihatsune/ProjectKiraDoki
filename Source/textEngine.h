#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

using namespace std;

extern TTF_Font* font1;
extern TTF_Font* font2;

extern SDL_Surface* surface1 ;
extern SDL_Texture* texture1 ;

extern SDL_Surface* surface2;
extern SDL_Texture* texture2;

extern SDL_Rect srcRest ;
extern SDL_Rect desRect ;

extern string oldTextInput1;
extern string oldTextInput2;

extern string font[5];


void textInit();

void textSet1(SDL_Renderer* renderer, string textInput, int fontSize, int fontType, int forecolor, int posX, int posY);

