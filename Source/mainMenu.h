#include <SDL.h>
#include <SDL_mixer.h>

#include "imageEngine.h"
#include "mouseEvent.h"
#include "sfxEngine.h"
#include "musicEngine.h"
#include "textEngine.h"
#include "newGame.h"

string songs[10] = { "Your Reality", "Fur Elise", "not added yet 3", "not added yet 4", "not added yet 5 ","not added yet 6", "not added yet 7", "not added yet 8", "not added yet 9", "not added yet 10" };
string modes[3] = { "Easy", "Medium", "Hard" };
string characters[3] = { "Character", "select is not", "available yet." };
string songinstant[10];

int easybpm[10] = { 60, 73, 0, 0, 0, 0, 0, 0, 0, 0 };
float easyspeed[10] = { 3.4, 3.7, 0, 0, 0, 0, 0, 0, 0, 0 };

int mediumbpm[10] = { 120, 73*2, 0, 0, 0, 0, 0, 0, 0, 0 };
float mediumspeed[10] = { 5.5, 6.0, 0, 0, 0, 0, 0, 0, 0, 0 };

int hardbpm[10] = { 210, 292, 0, 0, 0, 0, 0, 0, 0, 0 };
float hardspeed[10] = { 8.0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };

bool songchecked[10];
bool modechecked[3];
bool charchecked[3];

const int SONG_POS_START_X = 94, SONG_POS_END_X = 333, SONG_POS_START_Y = 181;
const int MODE_POS_START_X = 369, MODE_POS_END_X = 540, MODE_POS_START_Y = 446;

bool welcomecheck = true;


void initMedia();
void showMenu(SDL_Renderer* renderer, int n);

void initMedia()
{
	textInit();
}

void songPicker(SDL_Renderer* renderer)
{
	SDL_Event e;
	bool backPressed = false, playPressed = false;
	int bpmin;
	float speedin;

	//INITIALIZE
	int pickedsong = 0;
	songchecked[0] = true;
	for (int i = 1; i<10; i++) songchecked[i] = false;
	modechecked[0] = true;
	modechecked[1] = false;
	modechecked[2] = false;
	charchecked[0] = true;

	SDL_Texture* picker = NULL;
	SDL_Rect desRect;
	int w, h;
	picker = IMG_LoadTexture(renderer, "resources/songpick1.png");
	SDL_QueryTexture(picker, NULL, NULL, &w, &h);
	SDL_Rect texr;
	texr.x = 0;
	texr.y = 0;
	texr.w = w;
	texr.h = h;

	while (backPressed == false)
	{
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_Rect filled_rect;
		SDL_RenderCopy(renderer, picker, NULL, &texr);

		for (int i = 0; i < 10; i++)
			if (checkMouseHover(95, 181 + i * 40, 333, 181 + i * 40 + 40) == true && songchecked[i] != true)
			{
				imageShow(renderer, "resources/hoverchoose.png", 83, 170 + i * 40);
			}

		//CHECK HOVER PLAY BUTTON
		if (checkMouseHover(1017, 551, 1017 + 80, 551 + 150) == true)
			imageShow(renderer, "resources/playbuttonpressed.png", 1017, 551);
		else imageShow(renderer, "resources/playbutton.png", 1017, 551);

		//CHECK HOVER BACK BUTTON
		if (checkMouseHover(27, 75, 66, 119) == true)
			imageShow(renderer, "resources/back1pressed.png", 24, 67);
		else imageShow(renderer, "resources/back1.png", 24, 67);


		//HANDLE MODE//////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < 3; i++)
		{
			if (checkMouseHover(MODE_POS_START_X, MODE_POS_START_Y + i * 40, MODE_POS_END_X, MODE_POS_START_Y + i * 40 + 40) == true && modechecked[i] != true)
				imageShow(renderer, "resources/hover2choose.png", MODE_POS_START_X - 12, MODE_POS_START_Y - 6 + i * 40);
		}
		if (modechecked[0] == true)
		{
			imageShow(renderer, "resources/chosen2choose_blue.png", MODE_POS_START_X - 12, MODE_POS_START_Y - 6);
			bpmin = easybpm[pickedsong];
			speedin = easyspeed[pickedsong];
		}
		if (modechecked[1] == true)
		{
			imageShow(renderer, "resources/chosen2choose_orange.png", MODE_POS_START_X - 12, MODE_POS_START_Y - 6 + 40);
			bpmin = mediumbpm[pickedsong];
			speedin = mediumspeed[pickedsong];
		}
		if (modechecked[2] == true)
		{
			imageShow(renderer, "resources/chosen2choose_red.png", MODE_POS_START_X - 12, MODE_POS_START_Y - 6 + 80);
			bpmin = hardbpm[pickedsong];
			speedin = hardspeed[pickedsong];
		}
		///////////////////////////////////////////////////////////////////////////////////////////////

		for (int i = 0; i < 3; i++)
		{
			if (modechecked[i] != true)
				textSet1(renderer, modes[i], 30, 0, 1, MODE_POS_START_X + 12, MODE_POS_START_Y + 5 + i * 40);
			else	textSet1(renderer, modes[i], 30, 0, 2, MODE_POS_START_X + 12, MODE_POS_START_Y + 5 + i * 40);
		}



		//PICK CHARACTER
		for (int i = 0; i < 3; i++)
			textSet1(renderer, characters[i], 30, 0, 1, 589, 450 + i * 40);



		//PICK SONG
		for (int i = 0; i < 10; i++)
		{
			//HOVER
			if (checkMouseHover(SONG_POS_START_X, SONG_POS_START_Y + i * 40, SONG_POS_END_X, SONG_POS_START_Y + i * 40 + 40) == true && songchecked[i] != true)
				imageShow(renderer, "resources/hoverchoose.png", SONG_POS_START_X - 12, SONG_POS_START_Y - 11 + i * 40);
			//PRESSED & TEXT
			if (songchecked[i] == true)
			{
				imageShow(renderer, "resources/chosenchoose_blue.png", SONG_POS_START_X - 12, SONG_POS_START_Y - 11 + i * 40);
				textSet1(renderer, songs[i], 30, 0, 2, SONG_POS_START_X + 12, SONG_POS_START_Y + i * 40);
			}
			else	textSet1(renderer, songs[i], 30, 0, 1, SONG_POS_START_X + 12, SONG_POS_START_Y + i * 40);
		}

		//CONTROL WITH MOUSE
		while (SDL_PollEvent(&e) != 0) //continue;
		{
			int mX = e.button.x;
			int mY = e.button.y;
			if (e.type == SDL_QUIT) break;
			else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
				//PLAY BUTTON
				if (mX > 1017 && mY > 551 && mX < 1017 + 80 && mY < 551 + 150)
				{
					Mix_HaltMusic();
					sfxPlay(2);
					//showMenu(renderer, 2);
					gameStart(renderer, bpmin, speedin, pickedsong);
				}
				else if (mX > 27 && mY > 75 && mX < 66 && mY < 119)
				{
					Mix_HaltMusic();
					sfxPlay(2);
					showMenu(renderer, 2);
				}
				//DROP DOWN LISTS
				else
				{
					for (int q = 0; q < 10; q++)
						if (mX > SONG_POS_START_X &&
							mY > SONG_POS_START_Y + q * 40 &&
							mX < SONG_POS_END_X &&
							mY < SONG_POS_START_Y + q * 40 + 40)
						{
							songchecked[q] = true;
							pickedsong = q;
							for (int k = 0; k < 10; k++)
								if (k != q) songchecked[k] = false;
						}

					for (int q = 0; q < 3; q++)
						if (mX > MODE_POS_START_X &&
							mY > MODE_POS_START_Y + q * 40 &&
							mX < MODE_POS_END_X &&
							mY < MODE_POS_START_Y + q * 40 + 40)
						{
							modechecked[q] = true;
							for (int k = 0; k < 3; k++)
								if (k != q) modechecked[k] = false;
						}
				}
		}
	}
}


void showMenu(SDL_Renderer* renderer, int n)
{
    musicPlay("songs/theme.ogg");
	//n = animation mode: 1 = start game, 2 = from songPicker

    if (n == 1)
    {
        SDL_RenderClear(renderer);
        imageShow(renderer, "resources/welcome1.png", 0, 0);
        SDL_RenderPresent(renderer);

        SDL_Delay(2000);

        SDL_RenderClear(renderer);
        imageShow(renderer, "resources/welcomescreen.png", -1280, 0);
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);

        for (int i = -1280; i < 0; i += 40)
            {
                SDL_RenderClear(renderer);
                imageShow(renderer, "resources/welcomescreen.png", i, 0);
                SDL_RenderPresent(renderer);
            }
        for (int i = -348; i < 0; i += 40)
        {
            SDL_RenderClear(renderer);
            imageShow(renderer, "resources/songpick1.png", -1280, 0);
            imageShow(renderer, "resources/menu0.png", 0 + i, 0);
            SDL_RenderPresent(renderer);
        }
    }
	if (n == 2)
	{

		for (int i = 0; i >= -1280; i = i -= 50)
		{
			SDL_RenderClear(renderer);
			imageShow(renderer, "resources/songpick1.png", i, 0);
			SDL_RenderPresent(renderer);
		}

		for (int i = -348; i < 0; i += 40)
		{
			SDL_RenderClear(renderer);
			imageShow(renderer, "resources/songpick1.png", -1280, 0);
			imageShow(renderer, "resources/menu0.png", 0 + i, 0);
			SDL_RenderPresent(renderer);
		}

	}

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
			if (e.type == SDL_QUIT) break;
            else if (e.type == SDL_MOUSEBUTTONDOWN) {

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

            for (int i = -1280; i <= 0; i = i += 50 )
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