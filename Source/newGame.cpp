#pragma once
#include <SDL.h>;
#include <SDL_mixer.h> 

#include "noteHandle.h";

#include "sdl_utils.h";
#include "beatFrameStablizer.h"
#include "textEngine.h"
#include "imageEngine.h"
#include "musicEngine.h"
#include "sfxEngine.h"
#include "mouseEvent.h"
#include "gameconfig.h"

SDL_Texture* stage = NULL;
SDL_Texture* stageblack = NULL;
SDL_Texture* charimg = NULL;
SDL_Texture* thugimg = NULL;
SDL_Texture* firework1 = NULL;
SDL_Texture* firework2 = NULL;
SDL_Rect texr, texr1, chartexr;
SDL_Event gameEvent;
Uint32 frameStart;

//for game control
bool gamePause, gameExit, countdownActivated, gameLose, pauseStartRecord = false;
int lastPressed;

//for fever mode
bool feverChargeActivated, feverChargeCompleted, feverAnimation, feverNoti = true;
int frameFinished;
int feverChargeState;
int feverChargePress;
int feverChargeMax;


//for zoom animation
int zoom;
bool zoomfinish;

//for effect text
float effectpos;
int effectalpha, effectframecount;
bool phase1, hold, phase2;
bool effectanimation;
int effectType;

//other
int maxhealth[3] = { 20,20,15 };
int random[5] = { 1,2,3,4,5 };
Timer songTime;

//initializing variables
void initGuide(SDL_Renderer* rendGame, int character)
{
    SDL_ShowCursor(SDL_DISABLE);
    
    musicPlay("songs/startgame.ogg");
    SDL_SetRenderDrawColor(rendGame, 0, 0, 0, 255);
    for (int i = 0; i <= 255; i += 10)
    {
        SDL_RenderClear(rendGame);
        blendShow(rendGame, "resources/shadowguide.png", 0, 0, i);
        SDL_RenderPresent(rendGame);
    }
    for (int i = 0; i <= 255; i += 5)
    {
        SDL_RenderClear(rendGame);
        blendShow(rendGame, "resources/stage.png", 0, 0, i);
        blendShow(rendGame, charingame[character].c_str(), 800, 0, i);
        imageShow(rendGame, "resources/shadowguide.png", 0, 0);
        SDL_RenderPresent(rendGame);
    }

    imageShow(rendGame, "resources/stage.png", 0, 0);
    imageShow(rendGame, charingame[character].c_str(), 800, 0);
    imageShow(rendGame, "resources/shadowguide.png", 0, 0);
  
    SDL_RenderPresent(rendGame);
    SDL_Delay(5000);

    for (int i = 255; i >= 0; i -= 10)
    {
        SDL_RenderClear(rendGame);
        imageShow(rendGame, "resources/stage.png", 0, 0);
        imageShow(rendGame, charingame[character].c_str(), 800, 0);
        blendShow(rendGame, "resources/shadowguide.png", 0, 0, i);
        SDL_RenderPresent(rendGame);
    }
    SDL_ShowCursor(SDL_ENABLE);
}
void initStage(SDL_Renderer* rendGame, int character)
{
    int charw, charh;
    charimg = IMG_LoadTexture(rendGame, charingame[character].c_str());
    thugimg = IMG_LoadTexture(rendGame, thugingame[character].c_str());
    SDL_QueryTexture(charimg, NULL, NULL, &charw, &charh);

    chartexr.x = 800;
    chartexr.y = 0;
    chartexr.w = charw;
    chartexr.h = charh;

    int w, h;
    firework1 = IMG_LoadTexture(rendGame, "resources/firework1.png");
    firework2 = IMG_LoadTexture(rendGame, "resources/firework2.png");
    stage = IMG_LoadTexture(rendGame, "resources/stage.png");
    SDL_QueryTexture(stage, NULL, NULL, &w, &h);
    texr.x = 0; texr.y = 0; texr.w = w; texr.h = h;

    stageblack = IMG_LoadTexture(rendGame, "resources/fullblack.png");
    SDL_SetTextureBlendMode(stageblack, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(stageblack, 80);
    SDL_QueryTexture(stageblack, NULL, NULL, &w, &h);
    texr1.x = 0; texr1.y = 0; texr1.w = w; texr1.h = h;

}
void initGame(Note * n, int songBPM, float songSpeed, int character)
{
    gamePause = true;
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
    
    if (songBPM < 100 || songBPM == 121) feverChargeMax = 15;
    else if (songBPM < 200 || songBPM == 360) feverChargeMax = 30;
    else feverChargeMax = 45;

    zoom = 1000;
    zoomfinish = false;

    effectpos = 492;
    effectalpha = 0; effectframecount = 0;
    hold = false;
    phase2 = false;
    effectanimation = false;

    (*n).bpm = songBPM;
    (*n).speed = songSpeed;
    (*n).health = maxhealth[character];
    (*n).charskill = character;

    for (int i = 0; i < 10; i++)
        (*n).tileStatus[i] = false; 
}

//for effects
void renderGameObjects(SDL_Renderer* rendGame, Note n, int character, int song)
{
    //render background
    SDL_RenderCopy(rendGame, stage, NULL, &texr);
    SDL_RenderCopy(rendGame, charimg, NULL, &chartexr);
    if (songTime.get_ticks() > feverstart[song] && feverChargeCompleted == true)
    {
        SDL_RenderCopy(rendGame, thugimg, NULL, &chartexr);
        if (songTime.get_ticks() % 6000 < 3000)
            SDL_RenderCopy(rendGame, firework1, NULL, &texr);
        else
            SDL_RenderCopy(rendGame, firework2, NULL, &texr);    
    }
        
    if (feverChargeActivated == true) SDL_RenderCopy(rendGame, stageblack, NULL, &texr1);

    //render health bar
    if (n.health < maxhealth[character] / 4) SDL_SetRenderDrawColor(rendGame, 216, 61, 61, 255);
    else if (n.health >= maxhealth[character] / 4 && n.health <= maxhealth[character] / 2 + 2) SDL_SetRenderDrawColor(rendGame, 216, 165, 61, 255);
    else if (n.health > maxhealth[character] / 2 + 2) SDL_SetRenderDrawColor(rendGame, 47, 220, 93, 255);
    for (int i = 1; i < n.health; i++)
    {
        SDL_Rect filled_rect;
        filled_rect.x = 34 + (float)(i - 1) * ((float)238 / maxhealth[character]);
        filled_rect.y = 140;
        filled_rect.w = ((float)238 / maxhealth[character] + 3);
        filled_rect.h = 35;
        SDL_RenderFillRect(rendGame, &filled_rect);
    }

    //render score
    textSet1(rendGame, to_string(n.score), 32, 1, 2, 35, 60);

    textSet1(rendGame, to_string(songTime.get_ticks()), 25, 1, 2, 0, 0);
    
    //render lane mouse hover
    for (int i = 0; i < 5; i++)
        if (checkMouseHover(300 + i * 100, 0, 400 + i * 100, 720) == true)
             {
                    SDL_Rect hover_rect;
                     hover_rect.x = 300 + i  * 100;
                     hover_rect.y = 0;
                     hover_rect.w = 100;
                     hover_rect.h = 720;
                     SDL_SetRenderDrawColor(rendGame, 255, 255, 255, 30);
                     SDL_SetRenderDrawBlendMode(rendGame, SDL_BLENDMODE_BLEND);
                     SDL_RenderFillRect(rendGame, &hover_rect);
             }

    //render notes
    n.render(rendGame);


    //render lane line
    for (int i = 1; i < 5; i++)
    {
        SDL_Rect filled_rect;
        filled_rect.x = 300 + i * 100;
        filled_rect.y = 0;
        filled_rect.w = 2;
        filled_rect.h = 720;
        SDL_SetRenderDrawColor(rendGame, 240, 240, 240, 255);
        SDL_RenderFillRect(rendGame, &filled_rect);
    }

    //render stagelight
    if (feverChargeCompleted == true && songTime.get_ticks() > feverstart[song])
    {
        if (n.beat == true) 
            for (int i = 0; i < 5; i++)   random[i] = randomSpawn();
        for (int i = 0; i < 5; i++)
            imageShow(rendGame, stagelight[random[i]].c_str(), 300 + i * 100, 720 - 57);
    }
    else
    {
        for (int i = 0; i < 5; i++)
            imageShow(rendGame, stagelight[3].c_str(), 300 + i * 100, 720 - 57);
        imageShow(rendGame, stagelight[0].c_str(), 300 + lastPressed * 100, 720 - 57);
    }

   
}
void countdownActivate(SDL_Renderer* rendGame)
{
    blendShow(rendGame, "resources/countdown.png", 301, 297, 255);
    for (int i = 0; i<5; i++)
     imageShow(rendGame, stagelight[2].c_str(), 300 + i * 100, 720 - 57);
    textSet1(rendGame, "3", 50, 0, 2, 524, 331);
    sfxPlay(1);
    SDL_RenderPresent(rendGame);
    SDL_Delay(1000);

    blendShow(rendGame, "resources/countdown.png", 301, 297, 255);
    imageShow(rendGame, stagelight[3].c_str(), 300 + 0 * 100, 720 - 57);
    imageShow(rendGame, stagelight[3].c_str(), 300 + 4 * 100, 720 - 57);
    for (int i = 1; i < 4; i++)
        imageShow(rendGame, stagelight[1].c_str(), 300 + i * 100, 720 - 57);
    textSet1(rendGame, "2", 50, 0, 2, 524, 331);
    sfxPlay(1);
    SDL_RenderPresent(rendGame);
    SDL_Delay(1000);

    blendShow(rendGame, "resources/countdown.png", 301, 297, 255);
    for (int i = 0; i < 5; i++)
        imageShow(rendGame, stagelight[3].c_str(), 300 + i * 100, 720 - 57);
    imageShow(rendGame, stagelight[0].c_str(), 300 + 2 * 100, 720 - 57);
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
    songTime.unpause();
    countdownActivated = false;  
    gamePause = false;
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
    if (feverChargePress >= feverChargeMax / 2 + 1 && feverChargePress < feverChargeMax)  feverChargeState = 1;
    if (feverChargePress == feverChargeMax)
    {
        feverChargeState = 2;
        feverChargeCompleted = true;
    }

    for (int i = 0; i <= feverChargePress; i++)
    {
        SDL_Rect filled_rect;
        filled_rect.x = 387 + (float)i * ((float)166 / feverChargeMax);
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
            imageZoomShow(rendGame, feverchargeimage[feverChargeState].c_str(), 557, 328, zoom, zoom);  zoom += 6;
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
void effectActivate(SDL_Renderer* rendGame, int effectType) { 
    if (hold == true)
    {
        imageShow(rendGame, effectimage[effectType].c_str(), 300, effectpos);
        effectframecount++;
        if (effectframecount >= 90)
        {
            effectframecount = 0;
            hold = false;
            phase2 = true;
        }

    }
    else if (phase2 == true)
    {
        blendShow(rendGame, effectimage[effectType].c_str(), 300, effectpos, effectalpha);
        effectalpha -= 15;
        effectpos -= 0.2;
        if (effectalpha < 2)
        {

            phase2 = false;
            effectalpha = 0;
            phase1 = true;
            effectpos = 492;
            effectanimation = false;
        }
    }
    else
    {
            blendShow(rendGame, effectimage[effectType].c_str(), 300, effectpos, effectalpha);
            effectalpha += 15;
            effectpos -= 0.2;
            if (effectalpha >= 255)
            {
                effectalpha = 255;
                hold = true;
            }
    }


}
void destroyTexture() {
    SDL_DestroyTexture(stage); 
    SDL_DestroyTexture(stageblack); 
    SDL_DestroyTexture(charimg); 
    SDL_DestroyTexture(thugimg); 
    SDL_DestroyTexture(firework1); 
    SDL_DestroyTexture(firework2);
}

//game control
void gameStart(SDL_Renderer* rendGame, int songBPM, float songSpeed, int song, string songlocation, int character)
{
    Note n;  

    //initialize game
    initGuide(rendGame, character);
    initStage(rendGame,character);
    initGame(&n, songBPM, songSpeed, character);

    //play music
    musicPlay(songlocation.c_str()); Mix_PauseMusic();
    songTime.start();

    while (gameExit == false)
    {
        
        SDL_SetRenderDrawColor(rendGame, 255, 255, 255, 255); SDL_RenderClear(rendGame);

        //render game objects
        renderGameObjects(rendGame, n, character, song);

        if (gamePause == false)
        {
            //render pause button
            imageShow(rendGame, "resources/pause.png", PAUSE_X_START, PAUSE_Y_START);
            if (checkMouseHover(PAUSE_X_START, PAUSE_Y_START, PAUSE_X_END, PAUSE_Y_END) == true)
                imageShow(rendGame, "resources/pauseUIhighlight.png", PAUSE_X_START, PAUSE_Y_START);

            //move notes
            n.move();
            n.removeStatus();

            //active fever
            if (songTime.get_ticks() > feverchargestart[song] && songTime.get_ticks() < feverchargeend[song])
                feverCharge(rendGame);
            if (songTime.get_ticks() >= feverchargeend[song]) feverChargeActivated = false;
            if (songTime.get_ticks() > feverstart[song] && feverChargeCompleted == true)
            {
                if (feverNoti == true)
                {
                    effectanimation = true;
                    effectType = 4;
                    feverNoti = false;
                }
                n.score++;
            }

            //effect
            if (effectanimation == true)
                effectActivate(rendGame, effectType);
        }
        else pauseActivate(rendGame); //active pause UI

       
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
            else if (gameEvent.type == SDL_KEYDOWN)
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
                    if (n.tileLane[tileLastest] == 4) check = true; break;
                default: break;
                }

                if (check == true)
                {

                    if (songTime.get_ticks() > feverchargestart[song] && songTime.get_ticks() < feverchargeend[song] && feverChargePress < feverChargeMax)
                        feverChargePress++;
                    feverAnimation = true;
                    n.tilePress[tileLastest] = true;
                    n.score += scoreAdd[character] + rand() % 30;
                    if (n.tileSpecial[tileLastest] == true)
                    {
                        switch (character){
                        case 0:
                            n.health += rand() % 1 + 1;
                            effectanimation = true; effectType = 0;
                            break;
                        case 1:
                            n.score += rand() % 10 + 50;
                            effectanimation = true; effectType = 3;
                        case 2:
                           //random skill
                                if (rand() % 2 == 1 && n.health < maxhealth[character])
                                {
                                    n.health += rand() % 1 + 1;
                                    effectanimation = true; effectType = 0;
                                }
                                else
                                {
                                    n.score += rand() % 10 + 50;
                                    effectanimation = true; effectType = 3;
                                }

                             break;

                        }
                        
                    }
                    lastPressed = n.tileLane[tileLastest];
                }
                else if (gamePause == false)
                {
                    effectanimation = true; if (n.health < maxhealth[character] / 4) effectType = 2; else effectType = 1;
                    n.health--;
                }

            }
            else if (gameEvent.type == SDL_MOUSEBUTTONDOWN) {

                if (gameEvent.button.button == SDL_BUTTON_LEFT)
                {
                    int mouseX = gameEvent.button.x, mouseY = gameEvent.button.y;
                    if (mouseX > 38 && mouseY > 652 && mouseX < 172 && mouseY < 696)
                    {
                        Mix_PauseMusic();
                        gamePause = true;
                        songTime.pause();
                    }
                    else if (gamePause == false && countdownActivated == false)
                    {
                        bool check = false;
                        if (mouseX > 300 && mouseX < 400) if (n.tileLane[tileLastest] == 0) check = true;
                        if (mouseX > 400 && mouseX < 500) if (n.tileLane[tileLastest] == 1) check = true;
                        if (mouseX > 500 && mouseX < 600) if (n.tileLane[tileLastest] == 2) check = true;
                        if (mouseX > 600 && mouseX < 700) if (n.tileLane[tileLastest] == 3) check = true;
                        if (mouseX > 700 && mouseX < 800) if (n.tileLane[tileLastest] == 4) check = true;

                        if (check == true)
                        {
                            if (songTime.get_ticks() > feverchargestart[song] && songTime.get_ticks() < feverchargeend[song] && feverChargePress < feverChargeMax)
                                feverChargePress++;
                            feverAnimation = true;
                            n.tilePress[tileLastest] = true;
                            n.score += scoreAdd[character] + rand() % 30;
                            if (n.tileSpecial[tileLastest] == true)
                            {
                                switch (character) {
                                case 0:
                                    n.health += rand() % 1 + 1;
                                    effectanimation = true; effectType = 0;
                                    break;
                                case 1:
                                    n.score += rand() % 10 + 50;
                                    effectanimation = true; effectType = 3;
                                case 2:
                                    //random skill
                                    if (rand() % 2 == 1 && n.health < maxhealth[character])
                                    {
                                        n.health += rand() % 1 + 1;
                                        effectanimation = true; effectType = 0;
                                    }
                                    else
                                    {
                                        n.score += rand() % 10 + 50;
                                        effectanimation = true; effectType = 3;
                                    }

                                    break;

                                }

                            }
                            lastPressed = n.tileLane[tileLastest];
                        }
                        else if (mouseX > 300 && mouseX < 800 && gamePause == false)
                        {
                            effectanimation = true;  if (n.health < maxhealth[character] / 4) effectType = 2; else effectType = 1;
                            n.health--;
                        }
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

        //render
        SDL_RenderPresent(rendGame);

        //activate countdown
        if (countdownActivated == true)
        {
            SDL_ShowCursor(SDL_DISABLE);
            countdownActivate(rendGame);
            SDL_ShowCursor(SDL_ENABLE);
        }
        frameStart = SDL_GetTicks();

        if (n.health <= 0)
        {
            imageShow(rendGame, "resources/countdown.png", 301, 297);
            textSet1(rendGame, "You lose! Game exiting...", 35, 0, 2, 340, 331);
            SDL_RenderPresent(rendGame);
            Mix_HaltMusic();
            sfxPlay(2);
            SDL_Delay(4000);
            destroyTexture();
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
                textSet1(rendGame, "Your score is", 35, 0, 2, 340, 311 + 35);
                textSet1(rendGame, to_string(n.score), 35, 0, 2, 340, 311 + 35 * 2);
                SDL_RenderPresent(rendGame);
                Mix_HaltMusic();
                sfxPlay(2);
                SDL_Delay(4000); 
                destroyTexture();
                gameExit = true;
                break;
            }
        }
    }

}