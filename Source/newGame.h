#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

extern SDL_Texture* stage;
extern SDL_Texture* stageblack;
extern SDL_Rect texr,texr1;
extern SDL_Event gameEvent;
extern Uint32 frameStart;

extern bool gamePause, gameExit, countdownActivated, gameLose;
extern bool feverChargeActivated, feverChargeCompleted, feverAnimation;
extern int frameFinished;
extern int feverChargeState;
extern int feverChargePress;
extern int feverChargeMax;
extern int lastPressed;

extern int zoom; 
extern bool zoomfinish;

void initGuide(SDL_Renderer* rendGame);
void initStage(SDL_Renderer* rendGame);
void initGame();
void countdownActivate(SDL_Renderer* rendGame);
void pauseActivate(SDL_Renderer* rendGame);
void feverCharge(SDL_Renderer* rendGame);
void gameStart(SDL_Renderer* rendGame, int songBPM, float songSpeed, int song, std::string songlocation);