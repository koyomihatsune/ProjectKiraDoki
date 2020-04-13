#pragma once

#include <SDL.h>

bool checkMouseHover(int startx, int starty, int endx, int endy)
{
    int mouse_x, mouse_y;

    SDL_PumpEvents();

    SDL_GetMouseState(&mouse_x, &mouse_y);
    if (mouse_x > startx && mouse_y > starty && mouse_x < endx && mouse_y < endy)
        return true;
    else return false;
}
