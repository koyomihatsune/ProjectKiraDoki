#include <SDL.h>
#include <SDL_mixer.h>

#include <iostream>
#include <string>
#include <ctime>

#include "SDL_utils.h"
#include "mainMenu.h"

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
    initMedia();
    showMenu(renderer, 1);
    return 0;
}
