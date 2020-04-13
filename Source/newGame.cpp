#pragma once
#include <SDL.h>;
#include <SDL_mixer.h> 
#include <SDL_thread.h>
#include "noteHandle.h";
#include "sdl_utils.h";
#include "beatFrameStablizer.h"
#include "textEngine.h"
#include "imageEngine.h"
#include "songGuide.h"
#include "musicEngine.h"

using namespace std;
string songlocation[10] = { "songs/yourreality.ogg",
                                "Song 2",
                                "Song 3",
                                "Song 4",
                                "Song 5",
                                "Song 6",
                                "Song 7",
                                "Song 8",
                                "Song 9",
                                "Song 10" };

void gameStart(SDL_Renderer* rendGame, int songBPM, float songSpeed, int song)

{
    Note n;
    n.bpm = songBPM;
    n.speed = songSpeed;

    bool isRunning = true;
    SDL_Event gameEvent;
    Uint32 frameStart;
    gameEvent.key.keysym.sym = 0;

    //initialize stage
    SDL_Texture* stage = NULL;
    SDL_Rect desRect;
    int w, h;
    stage = IMG_LoadTexture(rendGame, "resources/stage.png");
    SDL_QueryTexture(stage, NULL, NULL, &w, &h);
    SDL_Rect texr;
    texr.x = 0; texr.y = 0; texr.w = w; texr.h = h;

    songGuide(rendGame);

    musicPlay(songlocation[song].c_str());
    while (true)
    {
        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rendGame, 255, 255, 255, 255);
        SDL_RenderClear(rendGame);
        //show stage
        SDL_RenderCopy(rendGame, stage, NULL, &texr);

        n.render(rendGame);
        n.move();
        n.removeStatus();
        textSet1(rendGame, to_string(n.score), 32, 1, 2, 35, 60);
        SDL_RenderPresent(rendGame);

        frameStablizer1(&n, &frameStart); //To make beat + stablize frame.
        float tilePosMax = 0;
        int tileLastest = -1;

        for (int b = 0; b < 10; b++)
            if (n.tileStatus[b] == true && n.tilePos[b] > tilePosMax && n.tilePress[b] != true)
            {
                tilePosMax = n.tilePos[b];
                tileLastest = b;
            }

        //cout << "The lastest note is now lane:" << n.tileLane[tileLastest] << " at pos " << tilePosMax  << endl;

        while (SDL_PollEvent(&gameEvent) != 0)
        {

            if (gameEvent.type == SDL_KEYDOWN)
            {
                bool check = false;
                switch (gameEvent.key.keysym.sym)
                {
                case SDLK_ESCAPE: break;
                case SDLK_x:
                    if (n.tileLane[tileLastest] == 0) check = true;
                    break;
                case SDLK_c:
                    if (n.tileLane[tileLastest] == 1) check = true;
                    break;
                case SDLK_v:
                    if (n.tileLane[tileLastest] == 2) check = true;
                    break;
                case SDLK_b:
                    if (n.tileLane[tileLastest] == 3) check = true;
                    break;
                case SDLK_n:
                    if (n.tileLane[tileLastest] == 4) check = true;
                    break;
                default: break;
                }
                if (check == true)
                {
                    n.tilePress[tileLastest] = true;
                    n.score += 1000;
                }
                else n.health--;

            }
            else if (gameEvent.type == SDL_MOUSEBUTTONDOWN) {

                if (gameEvent.button.button == SDL_BUTTON_LEFT)
                {
                    int mouseX = gameEvent.button.x, mouseY = gameEvent.button.y;
                    bool check = false;
                    if (mouseX > 300 && mouseX < 400) if (n.tileLane[tileLastest] == 0) check = true;
                    if (mouseX > 400 && mouseX < 500) if (n.tileLane[tileLastest] == 1) check = true;
                    if (mouseX > 500 && mouseX < 600) if (n.tileLane[tileLastest] == 2) check = true;
                    if (mouseX > 600 && mouseX < 700) if (n.tileLane[tileLastest] == 3) check = true;
                    if (mouseX > 700 && mouseX < 800) if (n.tileLane[tileLastest] == 4) check = true;
                    if (check == true)
                    {
                        n.tilePress[tileLastest] = true;
                        n.score += 1000;
                    }
                    else n.health--;
                }
            }


        }

        //Delay after song end
        if (Mix_PlayingMusic() == 0)
        {
            bool check = true;
            for (int r = 0; r < 10; r++)
                if (n.tileStatus[r] == true) check = false;
            if (check == true)
            {
                SDL_Delay(2000);
                break;
            }
        }
    }


}
