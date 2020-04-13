#pragma once
#include <SDL.h>;
#include <SDL_mixer.h> 

#include "noteHandle.h";
#include "sdl_utils.h";
#include "beatFrameStablizer.h"
#include "textEngine.h"
#include "imageEngine.h"

using namespace std;
string songlocation[10] = { "songs/yourreality.ogg",
                                "songs/furelise1.ogg",
                                "Song 3",
                                "Song 4",
                                "Song 5",
                                "Song 6",
                                "Song 7",
                                "Song 8",
                                "Song 9",
                                "Song 10" };
const int PAUSE_X_START = 39, PAUSE_Y_START = 653, PAUSE_X_END = 39+132, PAUSE_Y_END = 653+41;
const int CONTINUE_X_START = 399, CONTINUE_Y_START = 340, CONTINUE_X_END = 531, CONTINUE_Y_END = 381;
const int EXIT_X_START = 561, EXIT_Y_START = 340, EXIT_X_END = 696, EXIT_Y_END = 382;

void initGuide(SDL_Renderer* rendGame)
{
    musicPlay("songs/startgame.ogg");
    SDL_RenderClear(rendGame);
    imageShow(rendGame, "resources/stage.png", 0, 0);
    imageShow(rendGame, "resources/shadowguide.png", 0, 0);
    SDL_RenderPresent(rendGame);
    SDL_Delay(7000);
}

void gameStart(SDL_Renderer* rendGame, int songBPM, float songSpeed, int song)

{
    Note n;
    n.bpm = songBPM;
    n.speed = songSpeed;

    bool gamePause = false;
    bool gameExit = false;
    bool countdownActivated = true;
    bool gameLose = false;

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

    //intialize guide
    initGuide(rendGame);
    
    //intialize music
    musicPlay(songlocation[song].c_str());
    Mix_PauseMusic();

    while (gameExit == false)
    {
        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(rendGame, 255, 255, 255, 255);
        SDL_RenderClear(rendGame);

        //show stage

        SDL_RenderCopy(rendGame, stage, NULL, &texr);
        n.render(rendGame);

        if (countdownActivated == true)
        {

            imageShow(rendGame, "resources/countdown.png", 301, 297);
            textSet1(rendGame, "3", 50, 0, 2, 524, 331);
            sfxPlay(1);
            SDL_RenderPresent(rendGame);
            SDL_Delay(1000);

            imageShow(rendGame, "resources/countdown.png", 301, 297);
            textSet1(rendGame, "2", 50, 0, 2, 524, 331);
            sfxPlay(1);
            SDL_RenderPresent(rendGame);
            SDL_Delay(1000);

            imageShow(rendGame, "resources/countdown.png", 301, 297);
            textSet1(rendGame, "1", 50, 0, 2, 524, 331);
            sfxPlay(1);
            SDL_RenderPresent(rendGame);
            SDL_Delay(1000);

            imageShow(rendGame, "resources/countdown.png", 301, 297);
            textSet1(rendGame, "Game Start!", 50, 0, 2, 524 - 120, 331);
            sfxPlay(2);
            SDL_RenderPresent(rendGame);
            SDL_Delay(500);

            Mix_ResumeMusic();
            countdownActivated = false;
        }

        if (gamePause == false)
        {
                
                imageShow(rendGame, "resources/pause.png", PAUSE_X_START, PAUSE_Y_START);
                if (checkMouseHover(PAUSE_X_START, PAUSE_Y_START, PAUSE_X_END, PAUSE_Y_END) == true)
                    imageShow(rendGame, "resources/pauseUIhighlight.png", PAUSE_X_START, PAUSE_Y_START);
                n.move();
                n.removeStatus();
        }
        else
        {
            imageShow(rendGame, "resources/pauseUI.png", 300, 0);
            textSet1(rendGame, "Continue", 20, 1, 2, 412, 348);
            textSet1(rendGame, "Exit", 20, 1, 2, 593, 348);

            if (checkMouseHover(CONTINUE_X_START,CONTINUE_Y_START,CONTINUE_X_END,CONTINUE_Y_END) == true)
                imageShow(rendGame, "resources/pauseUIhighlight.png", CONTINUE_X_START, CONTINUE_Y_START);
            if (checkMouseHover(EXIT_X_START, EXIT_Y_START, EXIT_X_END, EXIT_Y_END) == true)
                imageShow(rendGame, "resources/pauseUIhighlight.png", EXIT_X_START, EXIT_Y_START);
        }

        textSet1(rendGame, to_string(n.score), 32, 1, 2, 35, 60);
        SDL_RenderPresent(rendGame);
 
        if (gamePause == false)
            frameStablizer1(&n, &frameStart);


        //find lastest tile
        float tilePosMax = 0;
        int tileLastest = -1;

        for (int b = 0; b < 10; b++)
            if (n.tileStatus[b] == true && n.tilePos[b] > tilePosMax && n.tilePress[b] != true)
            {
                tilePosMax = n.tilePos[b];
                tileLastest = b;
            }

        while (SDL_PollEvent(&gameEvent) != 0)
        {
            if (gameEvent.type == SDL_QUIT) break;
            else if (gameEvent.type == SDL_KEYDOWN && gamePause == false)
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
                    if (mouseX > 38 && mouseY > 652 && mouseX < 172 && mouseY < 696)
                    {
                        Mix_PauseMusic();
                        gamePause = true;
                    }
                    else if (gamePause == false)
                    {
                        
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
                    else if (gamePause == true)
                    {
                        if (mouseX > CONTINUE_X_START && mouseY > CONTINUE_Y_START && mouseX < CONTINUE_X_END && mouseY < CONTINUE_Y_END)
                        {
                            gamePause = false;
                            countdownActivated = true;
                        }
                        if (mouseX > EXIT_X_START && mouseY > EXIT_Y_START && mouseX < EXIT_X_END && mouseY < EXIT_Y_END)
                        {
                            gameExit = true;
                        }
                    }
                }
            }

    
        }

        if (n.health <= 0)
        {
            imageShow(rendGame, "resources/countdown.png", 301, 297);
            textSet1(rendGame, "You lose! Game exiting...", 35, 0, 2, 340, 331);
            SDL_RenderPresent(rendGame);
            Mix_HaltMusic();
            sfxPlay(2);
            SDL_Delay(4000);
            gameExit = true;
        }
        //Delay after song end
        if (Mix_PlayingMusic() == 0 && gameExit == false)
        {
            bool check = true;
            for (int r = 0; r < 10; r++)
                if (n.tileStatus[r] == true) check = false;
            if (check == true)
            {
                imageShow(rendGame, "resources/countdown.png", 301, 297);
                textSet1(rendGame, "Completed!", 35, 0, 2, 340, 311);
                textSet1(rendGame, "Your score is", 35, 0, 2, 340, 311+35);
                textSet1(rendGame, to_string(n.score), 35, 0, 2, 340, 311 + 35*2 );
                SDL_RenderPresent(rendGame);
                Mix_HaltMusic();
                sfxPlay(2);
                SDL_Delay(4000);
                break;
            }
        }



    }

    
}