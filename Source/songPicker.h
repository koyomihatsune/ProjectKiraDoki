#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include "imageEngine.h"
#include "newGame.h"

string songs[10] =			{ "Your Reality", "not added yet 2", "not added yet 3", "not added yet 4", "not added yet 5 ","not added yet 6", "not added yet 7", "not added yet 8", "not added yet 9", "not added yet 10" };
string modes[3] =			{ "Easy", "Medium", "Hard" };
string characters[3] =		{ "Aoi", "Rinna", "DJTuanLong" };

string songinstant[10];

int easybpm[10] =		{ 60, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float easyspeed[10] =	{ 3.4, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int mediumbpm[10] =		{ 120, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float mediumspeed[10] = { 5.5, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int hardbpm[10] =		{ 210, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float hardspeed[10] =	{ 8.0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

bool songchecked[10];
bool modechecked[3];
bool charchecked[3];

const int SONG_POS_START_X = 94, SONG_POS_END_X = 333, SONG_POS_START_Y = 181;
const int MODE_POS_START_X = 369, MODE_POS_END_X = 540, MODE_POS_START_Y = 446;

void songPicker(SDL_Renderer * renderer)
{
	SDL_Event e;
	bool backPressed = false, playPressed = false;
	int bpmin;
	float speedin;

	//INITIALIZE
	int pickedsong = 0;
	songchecked[0] = true;
	modechecked[0] = true;
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
				imageShow(renderer, "resources/hoverchoose.png", 83, 170 + i*40);
			}

		if (checkMouseHover(1017, 551, 1017 + 80, 551 + 150) == true)
		{
			imageShow(renderer, "resources/playbuttonpressed.png", 1017, 551);
			if (Mix_Playing(-1) != 1) sfxPlay(1);
		}
		else
		{
			Mix_HaltChannel(-1);
			imageShow(renderer, "resources/playbutton.png", 1017, 551);
		}

		//HANDLE MODE//////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < 3; i++)
		{
			if (checkMouseHover(MODE_POS_START_X, MODE_POS_START_Y + i * 40, MODE_POS_END_X, MODE_POS_START_Y + i * 40 + 40) == true && modechecked[i] != true)
				imageShow(renderer, "resources/hover2choose.png", MODE_POS_START_X - 12 , MODE_POS_START_Y - 6 + i * 40);
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
				    textSet1(renderer, modes[i], 30, 0, 1, MODE_POS_START_X + 12, MODE_POS_START_Y +5 + i * 40);
			else	textSet1(renderer, modes[i], 30, 0, 2, MODE_POS_START_X + 12, MODE_POS_START_Y +5 + i * 40);
		}



		//PICK CHARACTER
		for (int i = 0; i < 3; i++)
			textSet1(renderer, characters[i], 30, 0, 1, 589, 450 + i * 40);



		//PICK SONG
		for (int i = 0; i < 10; i++)
		{
			//HOVER
			if (checkMouseHover(SONG_POS_START_X, SONG_POS_START_Y + i * 40, SONG_POS_END_X, SONG_POS_START_Y + i * 40 + 40) == true && songchecked[i] != true)
				imageShow(renderer, "resources/hoverchoose.png", SONG_POS_START_X - 12 , SONG_POS_START_Y - 11 + i * 40);
			//PRESSED & TEXT
			if (songchecked[i] == true)
				{
					imageShow(renderer, "resources/chosenchoose_blue.png", SONG_POS_START_X - 12, SONG_POS_START_Y - 11 + i * 40);
					textSet1(renderer, songs[i], 30, 0, 2, SONG_POS_START_X + 12 , SONG_POS_START_Y + i * 40);
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
					gameStart(renderer, bpmin, speedin, pickedsong);
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
