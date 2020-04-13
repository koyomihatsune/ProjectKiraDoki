#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

using namespace std;

Mix_Chunk* chunk = NULL;

void sfxPlay(int sfxType)
{
    if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
        throw new exception("Cannot open SDL Audio");

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
        printf("%s", Mix_GetError());


    Mix_HaltChannel(-1);
    switch (sfxType)
    {
    case 1:
        chunk = Mix_LoadWAV("sfx/hover_long.ogg");
        break;
    case 2:
        chunk = Mix_LoadWAV("sfx/select.ogg");
        break;
    case 3:
        chunk = Mix_LoadWAV("sfx/gamestart.ogg");
        break;
    }
    Mix_PlayChannel(-1, chunk, 1);
}