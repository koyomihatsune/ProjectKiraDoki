#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_mixer.h>

#include "noteHandle.h"
#include "imageEngine.h"
#include "textEngine.h"

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
            {
               if (tileSpecial[i] != true)
                SDL_SetRenderDrawColor(renderer, 153, 204, 255, 255);
               else
               {
                   if (charskill == 1) //Hanako
                       SDL_SetRenderDrawColor(renderer, 204, 136, 0, 255);
                   else if (charskill == 0) //DJ Turo
                       SDL_SetRenderDrawColor(renderer, 0, 255, 191, 255);
               }
            }
            else
                SDL_SetRenderDrawColor(renderer, 149, 149, 149, 180); 
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_RenderFillRect(renderer, &filled_rect);

            if (tilePress[i] != true && tileSpecial[i] == true)
            {
                if (charskill == 1)
                 imageShow(renderer, "resources/scorenote.png", 300 + tileLane[i] * 100, (int)tilePos[i] - 150);
                if (charskill == 0)
                 imageShow(renderer, "resources/healthnote.png", 300 + tileLane[i] * 100, (int)tilePos[i] - 150);
            }
        }
}

void Note::removeStatus() //remove the note that is out of screen
{
    for (int k = 0; k < 10; k++)
        if (tileStatus[k] == true && tilePos[k] >= 720 + 120)
        {
            tileStatus[k] = false;
            tileSpecial[k] = false;
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
        specialNoteSpawn++;
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
                if (specialNoteSpawn == 30)
                {
                    tileSpecial[l] = true;
                    specialNoteSpawn = rand() % 5;
                }
                else tileSpecial[l] = false;
            }
            else l++;
            if (l == 10) check = true;
        }
    }
}


//From SDL Lazyfoo Tutorial
Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

int Timer::get_ticks()
{
    //If the timer is running
    if (started == true)
    {
        //If the timer is paused
        if (paused == true)
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}


void Timer::pause()
{
    //If the timer is running and isn't already paused
    if ((started == true) && (paused == false))
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if (paused == true)
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}



