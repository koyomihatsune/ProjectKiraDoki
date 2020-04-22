#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_mixer.h>

#include "noteHandle.h"
#include "imageEngine.h"

using namespace std;

void Note::render(SDL_Renderer* renderer)
{
    //render the notes
    for (int i = 0; i < 10; i++)
        if (tileStatus[i] == true)
        {
            SDL_Rect filled_rect;
            filled_rect.x = 300 + tileLane[i] * 100;
            filled_rect.y = (int)tilePos[i] - 150;
            filled_rect.w = 100;
            filled_rect.h = 150;
            if (tilePress[i] != true)
                SDL_SetRenderDrawColor(renderer, 153, 204, 255, 255);
            else
                SDL_SetRenderDrawColor(renderer, 149, 149, 149, 255); 
            SDL_RenderFillRect(renderer, &filled_rect);
        }
}

void Note::removeStatus() //remove the note that is out of screen
{
    for (int k = 0; k < 10; k++)
        if (tileStatus[k] == true && tilePos[k] >= 720 + 120)

        {
            tileStatus[k] = false;
            if (tilePress[k] == false) health--;
            cout << "Tile " << k << " at lane " << tileLane[k] << " at pos " << tilePos[k] << " removed." << endl;
        }
}

void Note::move() //move and spawn new notes
{

    spawnCheck = false;

    if (beat == true && Mix_PlayingMusic() != 0) spawnCheck = true;
    for (int k = 0; k < 10; k++)
        if (tileStatus[k] == true)
            tilePos[k] += speed;

    //Spawn a new note
    if (spawnCheck == true)
    {
        bool check = false; int l = 0;
        while (check == false)
        {
            if (tileStatus[l] != true)
            {
                check = true;
                tileStatus[l] = true;
                tilePos[l] = 0;
                tileLane[l] = randomSpawn();
                tilePress[l] = false;
            }
            else l++;
            if (l == 10) check = true;
        }
    }
}