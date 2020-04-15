#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>

using namespace std;

TTF_Font* font1 = NULL;
TTF_Font* font2 = NULL;

SDL_Surface* surface1 = NULL;
SDL_Texture* texture1 = NULL;

SDL_Surface* surface2 = NULL;
SDL_Texture* texture2 = NULL;

SDL_Rect srcRest;
SDL_Rect desRect;

string oldTextInput1;
string oldTextInput2;

string font[5] = { "fonts/Halogen.ttf" , "fonts/Aller_Rg.ttf", "fonts/RifficFree-Bold.ttf" };


void textInit()
{
	if (TTF_Init() < 0)
	{
		SDL_Log("%s", TTF_GetError());
	}
}

void textSet1(SDL_Renderer* renderer, string textInput, int fontSize, int fontType, int forecolor, int posX, int posY)
{
	if (textInput != oldTextInput1)
	{
		//Destroy it first so not make leak memory.
		SDL_DestroyTexture(texture1);
		TTF_CloseFont(font1);
		TTF_CloseFont(font2);
		//SDL_BlitSurface(surface1, NULL, surface1, NULL);

		//setup everything
		font1 = TTF_OpenFont(font[fontType].c_str(), fontSize);
		SDL_Color fg;

		switch (forecolor)
		{
		case 1: fg = { 0, 0, 0 }; break; //BLACK
		case 2: fg = { 255, 255, 255 }; break; //WHITE
		case 3: fg = { 153, 138, 211 }; break; //VIOLET
		case 4: fg = { 205, 241, 175 }; break; //TEA GREEN
		case 5: fg = { 136, 187, 228 }; break; //AERO
		case 6: fg = { 248, 209, 224 }; break; //CLASSIC ROSE
		//Source: https://www.schemecolor.com/pastel-wedding-theme-colors.php
		}
		surface1 = TTF_RenderText_Blended(font1, textInput.c_str(), fg);

		texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
		SDL_FreeSurface(surface1);
		TTF_SizeText(font1, textInput.c_str(), &srcRest.w, &srcRest.h);

		srcRest.x = 0;
		srcRest.y = 0;

		desRect.x = posX;
		desRect.y = posY;

		desRect.w = srcRest.w;
		desRect.h = srcRest.h;

		oldTextInput1 = textInput;
	}

	SDL_RenderCopy(renderer, texture1, &srcRest, &desRect);
}

