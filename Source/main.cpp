#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <string>
#include <ctime>

#include "SDL_utils.h"
#include "mainMenu.h"
//#include "imageEngine.h"



bool welcome = false;

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const string WINDOW_TITLE = "The Kira Kira Doki Doki Rhythm Game";

SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char* argv[])
{
	initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    srand(time(0));
    initMedia(); showMenu(renderer, 2); //for welcome screen and intialization change 2 to 1;
 
   // SDL_Delay(3000);

   // float effectpos = 492;
   //  int effectalpha=0, framecount=0;
   // bool finish = false, phase1=true, hold=false, phase2=false;
   // bool effectanimation = true;

   // SDL_Delay(3000);
   // while (effectanimation == true)
   // {
   //     SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); SDL_RenderClear(renderer);
   //    
   //     

   //     SDL_RenderPresent(renderer);
   //    
   // }
   //
   
    return 0;
}
