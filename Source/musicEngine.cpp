#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

using namespace std;

Mix_Music* music = NULL;

void musicPlay(const char songPath[])
{
    
    if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
        throw new exception("Cannot open SDL Audio");
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        std::cout << "Error:" << Mix_GetError() << std::endl;
    music = Mix_LoadMUS(songPath);
    Mix_PlayMusic(music, 1);
}