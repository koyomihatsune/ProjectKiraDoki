#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <SDL_mixer.h>
#include "imageEngine.h"

string stagelight[5] = { "resources/bottomlane_1.png", "resources/bottomlane_2.png", "resources/bottomlane_3.png", "resources/bottomlane_4.png", "resources/bottomlane_2.png" };
using namespace std;

int randomSpawn();

extern struct Note
{
    //CONTROL & SPAWN NOTE VARIABLES
    bool tileStatus[10];    //in lane = true, out of lane = false
    float tilePos[10];      //position on screen (from -150 -> 720)
    int tileLane[10];       //x: 1/2/3/4 combine with randomSpawn();
    bool tilePress[10];     //pressed = true - not pressed = false;
    
    //HEALTH AND SCORE COUNT
    int health = 20;
    int score = 0;

    bool spawnCheck = false;

    //CONTROL SPEED AND DIFFICULTY VARIABLES
    int bpm;  //beats per minutes variety btwn songs. the demo yourreality_2m.ogg has 105 bpm
    float speed;    //120-5.5 //420-17 //210-8 // change varieties depends on songs
    bool beat = true; //beat created with beatFrameStablizer
    
    

    void render(SDL_Renderer* renderer)
    {
        //render the lane
        for (int i = 1; i < 5; i++)
        {
            SDL_Rect filled_rect;
            filled_rect.x = 300+i*100;
            filled_rect.y = 0;
            filled_rect.w = 2;
            filled_rect.h = 720;
            SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255);
            SDL_RenderFillRect(renderer, &filled_rect);
        }

        //render health bar
        if (health <9) SDL_SetRenderDrawColor(renderer, 216, 61, 61, 255);
        else if (health >= health/4+1 && health <= health/2+1) SDL_SetRenderDrawColor(renderer, 216, 165, 61, 255);
        else if (health > health/2+1) SDL_SetRenderDrawColor(renderer, 47, 220, 93, 255);
        for (int i = 1; i < health; i++)
        {
            SDL_Rect filled_rect;
            filled_rect.x = 34+(i-1)*12;
            filled_rect.y = 140;
            filled_rect.w = 12;
            filled_rect.h = 35;
            SDL_RenderFillRect(renderer, &filled_rect);
        }

        //render the notes
        for (int i = 0; i < 10; i++)
            if (tileStatus[i] == true)
            {
                SDL_Rect filled_rect;
                filled_rect.x = 300+ tileLane[i] * 100;
                filled_rect.y = (int) tilePos[i]-150;
                filled_rect.w = 100;
                filled_rect.h = 150;
                if (tilePress[i] != true)

                {
                  //imageShow(renderer, "resources/note_blue.png", 300 + tileLane[i] * 100, (int)tilePos[i] - 150);
                  SDL_SetRenderDrawColor(renderer, 153, 204, 255, 255);
                }
                else
                  //imageShow(renderer, "resources/notepressed_blue.png", 301 + tileLane[i] * 100, (int)tilePos[i] - 150);
                  SDL_SetRenderDrawColor(renderer, 149, 149, 149, 255); //blue
               SDL_RenderFillRect(renderer, &filled_rect);
            }
    }


    void removeStatus() //remove the note that is out of screen
    {
        for (int k = 0; k < 10; k++)
            if (tileStatus[k] == true && tilePos[k] >= 720 + 120)

            {
                tileStatus[k] = false;
                if (tilePress[k] == false) health--;
                cout << "Tile " << k << " at lane " << tileLane[k] << " at pos " << tilePos[k] << " removed." << endl; 
            }
        
    }

    void move() //move and spawn new notes
    {

        spawnCheck = false;
        if (beat == true && Mix_PlayingMusic() != 0) spawnCheck = true;
        for (int k = 0; k < 10; k++)
            if (tileStatus[k] == true)
                tilePos[k] += speed;

        //Spawn a new note
        if (spawnCheck == true )
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



};



