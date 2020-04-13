#include <SDL.h>
#include <SDL_mixer.h>

#include "imageEngine.h"
#include "mouseEvent.h"
#include "sfxEngine.h"
#include "musicEngine.h"
#include "textEngine.h"

#include "songPicker.h"

void initMedia()
{
    textInit();
}

void showMenu(SDL_Renderer* renderer, bool* wcheck)
{
    musicPlay("songs/theme.ogg");
    if (*wcheck == false)
    {
        SDL_RenderClear(renderer);
        imageShow(renderer, "resources/welcome1.png", 0, 0);
        SDL_RenderPresent(renderer);

        SDL_Delay(2000);

        SDL_RenderClear(renderer);
        imageShow(renderer, "resources/welcomescreen.png", -1280, 0);
        SDL_RenderPresent(renderer);
        SDL_Delay(4000);

        bool menuShow = false;
        for (int i = -1280; i < 0; i += 40)
        {
            SDL_RenderClear(renderer);
            imageShow(renderer, "resources/welcomescreen.png", i, 0);
            SDL_RenderPresent(renderer);
            if (i > 0) menuShow = true;
        }
        for (int i = -348; i < 0; i += 40)
        {
            SDL_RenderClear(renderer);
            imageShow(renderer, "resources/songpick1.png", -1280, 0);
            imageShow(renderer, "resources/menu0.png", 0 + i, 0);
            SDL_RenderPresent(renderer);
        }
        *wcheck = true;
    }
    bool exitBoxShow = false;

    bool songPickerShow = false;
    SDL_Event e;

    while (songPickerShow == false)
    {
        SDL_RenderClear(renderer);
        imageShow(renderer, "resources/background.png", 0, 0);
        if (checkMouseHover(69, 441, 167, 496) == true)
        {
            imageShow(renderer, "resources/menuplay.png", 0, 0);
            if (Mix_Playing(-1) != 1) sfxPlay(1);
        }
        else if (checkMouseHover(69, 521, 192, 554) == true)
        {
            imageShow(renderer, "resources/menusettings.png", 0, 0);
            if (Mix_Playing(-1) != 1) sfxPlay(1);
        }
        else if (checkMouseHover(69, 567, 135, 606) == true)
        {
            imageShow(renderer, "resources/menuhelp.png", 0, 0);
            if (Mix_Playing(-1) != 1) sfxPlay(1);
        }
        else if (checkMouseHover(69, 620, 133, 659) == true)
        {
            imageShow(renderer, "resources/menuquit.png", 0, 0);
            if (Mix_Playing(-1) != 1) sfxPlay(1);
        }
        else
        {
            Mix_HaltChannel(-1);
            imageShow(renderer, "resources/menu0.png", 0, 0);
        }


        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_MOUSEBUTTONDOWN) {

                if (e.button.button == SDL_BUTTON_LEFT)
                    if (e.button.x > 69 && e.button.y > 441 && e.button.x < 167 && e.button.y < 496)
                    {
                        int Mix_HaltMusic();
                        sfxPlay(2);
                        songPickerShow = true;
                    }
                    else if (e.button.x > 69 && e.button.y > 620 && e.button.x < 133 && e.button.y < 659)
                    {
                        SDL_Quit();
                    }
            }
        }


        if (songPickerShow == true)
        {
            for (int i = 0; i > -348; i -= 40)
            {
                SDL_RenderClear(renderer);
                imageShow(renderer, "resources/songpick1.png", -1280, 0);
                imageShow(renderer, "resources/menuplay.png", 0 + i, 0);
                SDL_RenderPresent(renderer);
            }

            for (int i = -1280; i <= 0; i = i += 50)
            {
                SDL_RenderClear(renderer);
                imageShow(renderer, "resources/songpick1.png", i, 0);
                SDL_RenderPresent(renderer);
            }

            songPicker(renderer);
        }

        SDL_RenderPresent(renderer);

    }
}