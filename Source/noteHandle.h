#pragma once
#include <SDL.h>

using namespace std;

int randomSpawn();

extern struct Note
{
    //CONTROL & SPAWN NOTE VARIABLES
    bool tileStatus[10];    //in lane = true, out of lane = false
    float tilePos[10];      //position on screen (from -150 -> 720)
    int tileLane[10];       //x: 1/2/3/4 combine with randomSpawn();
    bool tilePress[10];     //pressed = true - not pressed = false;
    bool tileSpecial[10];
    
    //HEALTH AND SCORE COUNT
    int health = 20;
    int score = 0;
    int charskill;
    int specialNoteSpawn = 0;

    bool spawnCheck = false;

    //CONTROL SPEED AND DIFFICULTY VARIABLES
    int bpm;  //beats per minutes variety btwn songs. the demo yourreality_2m.ogg has 105 bpm
    float speed;    //120-5.5 //420-17 //210-8 // change varieties depends on songs
    bool beat = true; //beat created with beatFrameStablizer

    void render(SDL_Renderer* renderer);
    void removeStatus();
    void move();
};

extern class Timer
{
private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();
};


