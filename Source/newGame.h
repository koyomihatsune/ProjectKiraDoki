#pragma once
#include <SDL.h>;
#include <SDL_mixer.h> 

#include "noteHandle.h";
#include "sdl_utils.h";
#include "beatFrameStablizer.h"
#include "textEngine.h"
#include "imageEngine.h"
#include "gameconfig.h"

SDL_Texture* stage = NULL;
SDL_Texture* stageblack = NULL;
SDL_Rect texr,texr1;
SDL_Event gameEvent;
Uint32 frameStart;

bool gamePause, gameExit, countdownActivated, gameLose;
bool feverChargeActivated, feverChargeCompleted, feverAnimation;
int frameFinished;
int feverChargeState;
int feverChargePress;
int feverChargeMax;
int lastPressed;

int zoom; bool zoomfinish;

void initGuide(SDL_Renderer* rendGame)
{
    musicPlay("songs/startgame.ogg");
    SDL_RenderClear(rendGame);
    imageShow(rendGame, "resources/stage.png", 0, 0);
    imageShow(rendGame, "resources/shadowguide.png", 0, 0);
    SDL_RenderPresent(rendGame);
    SDL_Delay(7000);
}
void initStage(SDL_Renderer* rendGame)
{
    int w, h;
    stage = IMG_LoadTexture(rendGame, "resources/stage.png");
    SDL_QueryTexture(stage, NULL, NULL, &w, &h);
    texr.x = 0; texr.y = 0; texr.w = w; texr.h = h;

    stageblack = IMG_LoadTexture(rendGame, "resources/fullblack.png");
    SDL_SetTextureBlendMode(stageblack, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(stageblack, 80);
    SDL_QueryTexture(stageblack, NULL, NULL, &w, &h);
    texr1.x = 0; texr1.y = 0; texr1.w = w; texr1.h = h;

}
void countdownActivate(SDL_Renderer* rendGame)
{
    blendShow(rendGame, "resources/countdown.png", 301, 297,180);
    textSet1(rendGame, "3", 50, 0, 2, 524, 331);
    sfxPlay(1);
    SDL_RenderPresent(rendGame);
    SDL_Delay(1000);

    blendShow(rendGame, "resources/countdown.png", 301, 297, 180);
    textSet1(rendGame, "2", 50, 0, 2, 524, 331);
    sfxPlay(1);
    SDL_RenderPresent(rendGame);
    SDL_Delay(1000);

    blendShow(rendGame, "resources/countdown.png", 301, 297,180);
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
void pauseActivate(SDL_Renderer* rendGame)
{
    imageShow(rendGame, "resources/pauseUI.png", 300, 0);
    textSet1(rendGame, "Continue", 20, 2, 2, 412, 348);
    textSet1(rendGame, "Exit", 20, 2, 2, 593, 348);

    if (checkMouseHover(CONTINUE_X_START, CONTINUE_Y_START, CONTINUE_X_END, CONTINUE_Y_END) == true)
        imageShow(rendGame, "resources/pauseUIhighlight.png", CONTINUE_X_START, CONTINUE_Y_START);
    if (checkMouseHover(EXIT_X_START, EXIT_Y_START, EXIT_X_END, EXIT_Y_END) == true)
        imageShow(rendGame, "resources/pauseUIhighlight.png", EXIT_X_START, EXIT_Y_START);
}
void feverCharge(SDL_Renderer* rendGame)
{
    feverChargeActivated = true;
    if (feverChargePress < feverChargeMax / 2 + 1) feverChargeState = 0;
    if (feverChargePress > feverChargeMax / 2 + 1 && feverChargePress < feverChargeMax)  feverChargeState = 1;
    if (feverChargePress == feverChargeMax)
    {
        feverChargeState = 2;
        feverChargeCompleted = true;
    }
    cout << feverChargeState << " " << feverChargePress << endl;

    for (int i = 0; i <= feverChargePress; i++)
    {
        SDL_Rect filled_rect;
        filled_rect.x = 384 + (float)i * ((float)166 / feverChargeMax);
        filled_rect.y = 328;
        filled_rect.w = (float)i * ((float)166 / feverChargeMax);
        filled_rect.h = 32;
        if (feverChargePress <= feverChargeMax / 3 - 1) SDL_SetRenderDrawColor(rendGame, 251, 123, 253, 255);
        else if (feverChargePress > feverChargeMax / 3 - 1 && feverChargePress < feverChargeMax / 2 + 1) SDL_SetRenderDrawColor(rendGame, 0, 195, 81, 255);
        else if (feverChargePress >= feverChargeMax / 2 + 1 && feverChargePress < feverChargeMax) SDL_SetRenderDrawColor(rendGame, 4, 202, 209, 255);
        else if (feverChargePress == feverChargeMax) SDL_SetRenderDrawColor(rendGame, 201, 216, 135, 255);
        SDL_RenderFillRect(rendGame, &filled_rect);
    }

    if (feverAnimation == true)
    {
        if (zoom < 1030 && zoomfinish == false)
        {
            imageZoomShow(rendGame, feverchargeimage[feverChargeState].c_str(), 557, 328, zoom, zoom);  zoom += 5;
        }
        if (zoom >= 1030) zoomfinish = true;
        if (zoom >= 1000 && zoomfinish == true)
        {
            imageZoomShow(rendGame, feverchargeimage[feverChargeState].c_str(), 557, 328, zoom, zoom);
            zoom -= 3;
            if (zoom == 1000)
            {
                zoomfinish = false;
                feverAnimation = false;
            }
        }
    }
    else
        imageZoomShow(rendGame, feverchargeimage[feverChargeState].c_str(), 557, 328, 1000, 1000);
    
}

void gameStart(SDL_Renderer* rendGame, int songBPM, float songSpeed, int song, string songlocation)
{
    Note n;  n.bpm = songBPM; n.speed = songSpeed;

    gamePause = false;
    gameExit = false;
    countdownActivated = true;
    gameLose = false;

    feverChargeActivated = false;
    feverChargeCompleted = false;
    feverAnimation = false;

    gameEvent.key.keysym.sym = 0;
    frameFinished = 0;
    feverChargeState = 0;
    feverChargePress = 0;
    feverChargeMax = 30;

    zoom = 1000;
    zoomfinish = false;
    int random[5] = { 1,2,3,4,5 };

    initGuide(rendGame);
    initStage(rendGame);
    musicPlay(songlocation.c_str()); Mix_PauseMusic();

    while (gameExit == false)
    {
        frameStart = SDL_GetTicks();
        frameFinished++;
        SDL_SetRenderDrawColor(rendGame, 255, 255, 255, 255); SDL_RenderClear(rendGame);
        SDL_RenderCopy(rendGame, stage, NULL, &texr);

        if (feverChargeActivated == true) SDL_RenderCopy(rendGame, stageblack, NULL, &texr1);

        n.render(rendGame);

        if (countdownActivated == true) countdownActivate(rendGame);


        //stagelight show normal
        for (int i = 0; i < 5; i++)
            imageShow(rendGame, stagelight[3].c_str(), 300 + i * 100, 720 - 57);
        imageShow(rendGame, stagelight[0].c_str(), 300 + lastPressed * 100, 720 - 57);


        //fever mode
        if (feverChargeCompleted == true && frameFinished > feverstart[song])
        {
            //stagelight show
            if (n.beat == true)
               for (int i = 0; i < 5; i++)   random[i] = randomSpawn();
            for (int i = 0; i < 5; i++)
                imageShow(rendGame, stagelight[random[i]].c_str(), 300 + i * 100, 720 - 57);
        }

        if (gamePause == false)
        {
            //pause button
            imageShow(rendGame, "resources/pause.png", PAUSE_X_START, PAUSE_Y_START);
            if (checkMouseHover(PAUSE_X_START, PAUSE_Y_START, PAUSE_X_END, PAUSE_Y_END) == true)
                imageShow(rendGame, "resources/pauseUIhighlight.png", PAUSE_X_START, PAUSE_Y_START);
            //move notes
            n.move();
            n.removeStatus();
            //active fever charging
            if (frameFinished > feverchargestart[song] && frameFinished < feverchargeend[song])
                feverCharge(rendGame);    
            if (frameFinished == feverchargeend[song]) feverChargeActivated = false;
        }
        //active pause UI
        else pauseActivate(rendGame);

        //show score
        textSet1(rendGame, to_string(n.score), 32, 1, 2, 35, 60);
        
        //DEBUG ONLY: show frame finished
        textSet1(rendGame, to_string(frameFinished), 32, 1, 2, 0, 0);

        SDL_RenderPresent(rendGame);

        //stablize frame and beat
        if (gamePause == false) frameStablizer1(&n, &frameStart);

        //find lastest tile
        float tilePosMax = 0; int tileLastest = -1;
        for (int b = 0; b < 10; b++)
            if (n.tileStatus[b] == true && n.tilePos[b] > tilePosMax && n.tilePress[b] != true)
            {
                tilePosMax = n.tilePos[b]; 
                tileLastest = b;
            }

        //game event
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
                    if (n.tileLane[tileLastest] == 0) check = true; break;
                case SDLK_c:
                    if (n.tileLane[tileLastest] == 1) check = true; break;
                case SDLK_v:
                    if (n.tileLane[tileLastest] == 2) check = true; break;
                case SDLK_b:
                    if (n.tileLane[tileLastest] == 3) check = true; break;
                case SDLK_n:
                    if (n.tileLane[tileLastest] == 4) check = true;
                    break;
                default: break;
                }
                if (check == true)
                {
                    if (frameFinished > feverchargestart[song] && frameFinished < feverchargeend[song] && feverChargePress < feverChargeMax) 
                        feverChargePress++;
                    feverAnimation = true;
                    n.tilePress[tileLastest] = true;
                    n.score += 1000;
                    lastPressed = n.tileLane[tileLastest];
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
                            if (frameFinished > feverchargestart[song] && frameFinished < feverchargeend[song] && feverChargePress < feverChargeMax)
                                feverChargePress++;
                            feverAnimation = true;
                            n.tilePress[tileLastest] = true;
                            n.score += 1000;
                            lastPressed = n.tileLane[tileLastest];
                        }
                        else n.health--;
                    }
                    else if (gamePause == true)
                    {
                        if (mouseX > CONTINUE_X_START && mouseY > CONTINUE_Y_START && mouseX < CONTINUE_X_END && mouseY < CONTINUE_Y_END)
                        {
                            gamePause = false; countdownActivated = true;
                        }
                        if (mouseX > EXIT_X_START && mouseY > EXIT_Y_START && mouseX < EXIT_X_END && mouseY < EXIT_Y_END)
                            gameExit = true;
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