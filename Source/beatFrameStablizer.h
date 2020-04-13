#pragma once
#include <SDL.h>;
#include <SDL_mixer.h>
#include "sdl_utils.h";

const int FPS = 60;
const int DELAY_TIME = 1000 / FPS;

float frameCount = 0;
float frameCountPrecise1 = 0;
Uint32 frameTime;


void frameStablizer1(Note * n, Uint32 * frameStart)
{
	float desired = 3600 / (*n).bpm;
	frameTime = SDL_GetTicks() - *frameStart;
	if (frameTime < DELAY_TIME)
	{
		SDL_Delay(DELAY_TIME - frameTime);
	}
	frameCount++;

	if (frameCount > desired)
	{
		frameCountPrecise1 += (frameCount - floorf(frameCount));
		frameCount = 0; 
		(*n).beat = true;
		if (frameCountPrecise1 > 1)
		{
			frameCount += frameCountPrecise1;
			frameCountPrecise1 = (frameCountPrecise1 - floorf(frameCountPrecise1));
		}
	}
	else (*n).beat = false; 

}



