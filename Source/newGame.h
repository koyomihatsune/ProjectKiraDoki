#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "noteHandle.h"

void initGuide(SDL_Renderer* rendGame, int character);
void initStage(SDL_Renderer* rendGame, int character);
void initGame(Note* n, int songBPM, float songSpeed, int character);
void renderGameObjects(SDL_Renderer* rendGame, Note n, int character, int song);
void countdownActivate(SDL_Renderer* rendGame);
void pauseActivate(SDL_Renderer* rendGame);
void feverCharge(SDL_Renderer* rendGame);
void effectActivate(SDL_Renderer* rendGame, int effectType);
void destroyTexture();
void gameStart(SDL_Renderer* rendGame, int songBPM, float songSpeed, int song, std::string songlocation, int character);