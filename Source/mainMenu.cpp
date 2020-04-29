#include <SDL.h>
#include <SDL_mixer.h>

#include "imageEngine.h"
#include "mouseEvent.h"
#include "sfxEngine.h"
#include "musicEngine.h"
#include "textEngine.h"
#include "newGame.h"
#include "UIconfig.h"
#include "songconfig.h"
#include "mainMenu.h"

bool songchecked[10];
bool modechecked[3];
bool charchecked[3];

//init
int pickedsong = 0;
int pickedchar = 0;

bool welcomecheck = true;
bool helpopen = false;
int backgroundPos = 0;

SDL_Texture* background1 = NULL; 
SDL_Texture* background2 = NULL;
SDL_Rect bkt1, bkt2;

void initMedia()
{
	textInit();
}
void welcomeAnimation(SDL_Renderer* renderer) 
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i <= 255; i += 10)
	{
		SDL_RenderClear(renderer);
		blendShow(renderer, "resources/welcome1.png", 0, 0, i);
		SDL_RenderPresent(renderer);
	}
	SDL_Delay(2000);
	for (int i = 255; i >= 0; i -= 10)
	{
		SDL_RenderClear(renderer);
		blendShow(renderer, "resources/welcome1.png", 0, 0, i);
		SDL_RenderPresent(renderer);
	}
	for (int i = 0; i <= 255; i += 10)
	{
		SDL_RenderClear(renderer);
		blendShow(renderer, "resources/welcomescreen.png", 0, 0, i);
		SDL_RenderPresent(renderer);
	}
	SDL_Delay(2000);
	for (int i = 255; i >= 0; i -= 10)
	{
		SDL_RenderClear(renderer);
		blendShow(renderer, "resources/welcomescreen.png", 0, 0, i);
		SDL_RenderPresent(renderer);
	}

	pickedsong = 0;
	pickedchar = rand() % 3;
	songchecked[0] = true;
	for (int i = 1; i < 10; i++) songchecked[i] = false;
	modechecked[0] = true;
	modechecked[1] = false;
	modechecked[2] = false;
	charchecked[pickedchar] = true;
	background1 = IMG_LoadTexture(renderer, background[pickedchar].c_str());
	background2 = IMG_LoadTexture(renderer, background[pickedchar].c_str());

	backgroundPos = 48;

	for (int i = 15; i <= 255; i += 10)
	{
		SDL_RenderClear(renderer);
		backgroundPos -= 2;
		blendShow(renderer, background[pickedchar].c_str(), backgroundPos, 0, i);
		blendShow(renderer, background[pickedchar].c_str(), backgroundPos - 1300, 0, i);
		SDL_RenderPresent(renderer);
	}

	backgroundPos = 0;

	for (int i = 0; i <= 255; i += 30)

	{
		SDL_RenderClear(renderer);
		showBackground(renderer, 1);
		blendShow(renderer, charimage[pickedchar].c_str(), 532, 0, i);
		blendShow(renderer, logo.c_str(), LOGO_POS_START_X, LOGO_POS_START_Y, i);
		blendShow(renderer, startbutton[pickedchar].c_str(), START_POS_START_X, START_POS_START_Y, i);
		blendShow(renderer, helpbutton[pickedchar].c_str(), HELP_POS_START_X, HELP_POS_START_Y, i);
		blendShow(renderer, quitbutton[pickedchar].c_str(), QUIT_POS_START_X, QUIT_POS_START_Y, i);
		SDL_RenderPresent(renderer);
	}
}
void showBackground(SDL_Renderer* renderer, int n)
{
	if (n == 1) backgroundPos -= 2;
	if (backgroundPos <= -1300) backgroundPos = 0;
	int w, h;
	SDL_QueryTexture(background1, NULL, NULL, &w, &h);
	SDL_QueryTexture(background1, NULL, NULL, &w, &h);

	bkt1.x = backgroundPos;
	bkt1.y = 0;
	bkt1.w = w;
	bkt1.h = h;

	bkt2.x = backgroundPos+1298;
	bkt2.y = 0;
	bkt2.w = w;
	bkt2.h = h;

	SDL_RenderCopy(renderer, background1, NULL, &bkt1);
	SDL_RenderCopy(renderer, background2, NULL, &bkt2);
}
void showUI(SDL_Renderer* renderer)
{
	showBackground(renderer, 1);
	imageShow(renderer, songpicktitle[pickedchar].c_str(), 88, 58);
	imageShow(renderer, songbox[pickedchar].c_str(), 92, 151);
	imageShow(renderer, charbox[pickedchar].c_str(), 365, 418);
	imageShow(renderer, charimage[pickedchar].c_str(), 532, 0);
	imageShow(renderer, charbox[pickedchar].c_str(), 572, 418);

	//CHECK HOVER PLAY BUTTON
	if (checkMouseHover(1017, 551, 1017 + 150, 551 + 80) == true)
		imageShow(renderer, playhover[pickedchar].c_str(), 1017, 551);
	else imageShow(renderer, playbutton[pickedchar].c_str(), 1017, 551);

	//CHECK HOVER BACK BUTTON
	if (checkMouseHover(27, 75, 66, 119) == true)
		imageShow(renderer, backhover[pickedchar].c_str(), 24, 67);
	else imageShow(renderer, backbutton[pickedchar].c_str(), 24, 67);

}
void showSongs(SDL_Renderer* renderer)
{
	//CHOSEN SONG
	for (int i = 0; i < 9; i++)
	{
		//HOVER SONG
		if (checkMouseHover(SONG_POS_START_X, SONG_POS_START_Y + i * 40, SONG_POS_END_X, SONG_POS_START_Y + i * 40 + 40) == true && songchecked[i] != true)
			if (i!=3) imageShow(renderer, hoverlong[pickedchar].c_str(), SONG_POS_START_X - 12, SONG_POS_START_Y - 11 + i * 40);

		//TEXT SONG
		if (songchecked[i] == true)
		{
			imageShow(renderer, chosenlong[pickedchar].c_str(), SONG_POS_START_X - 12, SONG_POS_START_Y - 11 + i * 40);
			textSet1(renderer, songs[i], 30, 0, 2, SONG_POS_START_X + 12, SONG_POS_START_Y + i * 40);
		}
		else textSet1(renderer, songs[i], 30, 0, 1, SONG_POS_START_X + 12, SONG_POS_START_Y + i * 40);
	}
}
void showModes(SDL_Renderer* renderer, int * bpmin, float * speedin)
{
	//CHOSEN MODE
	if (modechecked[0] == true)
	{
		imageShow(renderer, "resources/b/chosen2choose_green.png", MODE_POS_START_X - 12, MODE_POS_START_Y - 6);
		*bpmin = easybpm[pickedsong];
		*speedin = easyspeed[pickedsong];
	}
	if (modechecked[1] == true)
	{
		imageShow(renderer, "resources/b/chosen2choose_orange.png", MODE_POS_START_X - 12, MODE_POS_START_Y - 6 + 40);
		*bpmin = mediumbpm[pickedsong];
		*speedin = mediumspeed[pickedsong];
	}
	if (modechecked[2] == true)
	{
		imageShow(renderer, "resources/b/chosen2choose_red.png", MODE_POS_START_X - 12, MODE_POS_START_Y - 6 + 80);
		*bpmin = hardbpm[pickedsong];
		*speedin = hardspeed[pickedsong];
	}

	//HOVER & TEXT MODE
	for (int i = 0; i < 3; i++)
	{
		//HOVER MODE
		if (checkMouseHover(MODE_POS_START_X, MODE_POS_START_Y + i * 40, MODE_POS_END_X, MODE_POS_START_Y + i * 40 + 40) == true && modechecked[i] != true)
			imageShow(renderer, hovershort[pickedchar].c_str(), MODE_POS_START_X - 12, MODE_POS_START_Y - 6 + i * 40);
		//TEXT MODE
		if (modechecked[i] != true)
			textSet1(renderer, modes[i], 30, 0, 1, MODE_POS_START_X + 12, MODE_POS_START_Y + 5 + i * 40);
		else	textSet1(renderer, modes[i], 30, 0, 2, MODE_POS_START_X + 12, MODE_POS_START_Y + 5 + i * 40);
	}

}
void showChars(SDL_Renderer* renderer) {

	//CHOSEN CHAR
	for (int i = 0; i < 3; i++)
	{
		//HOVER
		if (checkMouseHover(CHAR_POS_START_X, CHAR_POS_START_Y + i * 40, CHAR_POS_END_X, CHAR_POS_START_Y + i * 40 + 40) == true && charchecked[i] != true)
			imageShow(renderer, hovershort[pickedchar].c_str(), CHAR_POS_START_X - 12, CHAR_POS_START_Y - 6 + i * 40);
		//CHOSEN CHAR
		if (charchecked[i] == true)
		{
			imageShow(renderer, chosenshort[pickedchar].c_str(), CHAR_POS_START_X - 12, CHAR_POS_START_Y - 6 + i * 40);
			textSet1(renderer, info[i * 4], 25, 0, 1, 372, 226);
			textSet1(renderer, info[i * 4 + 1], 25, 0, 1, 372, 258);
			textSet1(renderer, info[i * 4 + 2], 25, 0, 1, 372, 302);
			textSet1(renderer, info[i * 4 + 3], 25, 0, 1, 372, 334);
			
		}

		//TEXT CHAR
		if (charchecked[i] != true)
			textSet1(renderer, characters[i], 30, 0, 1, CHAR_POS_START_X + 12, CHAR_POS_START_Y + 5 + i * 40);
		else	textSet1(renderer, characters[i], 30, 0, 2, CHAR_POS_START_X + 12, CHAR_POS_START_Y + 5 + i * 40);
	}

}

void songPicker(SDL_Renderer* renderer)
{
	SDL_Event e;
	bool backPressed = false, playPressed = false;
	int bpmin;
	float speedin;

	//INITIALIZE
	Mix_HaltMusic();

	while (backPressed == false)
	{
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		showUI(renderer);
		showSongs(renderer);
		showModes(renderer, &bpmin, &speedin);
		showChars(renderer);

		//if ((SDL_PollEvent(&e) == 0)) continue; else 
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
					gameStart(renderer, bpmin, speedin, pickedsong, songlocation[pickedsong], pickedchar);
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
					for (int q = 0; q < 9; q++)
						if (mX > SONG_POS_START_X &&
							mY > SONG_POS_START_Y + q * 40 &&
							mX < SONG_POS_END_X &&
							mY < SONG_POS_START_Y + q * 40 + 40)
						{
							if (q!=3)
							{ 
								songchecked[q] = true;
								pickedsong = q;
								for (int k = 0; k < 10; k++)
									if (k != q) songchecked[k] = false;
							}
							
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


					for (int q = 0; q < 3; q++)
						if (mX > CHAR_POS_START_X &&
							mY > CHAR_POS_START_Y + q * 40 &&
							mX < CHAR_POS_END_X &&
							mY < CHAR_POS_START_Y + q * 40 + 40)
						{
							charchecked[q] = true;
							pickedchar = q;
							for (int k = 0; k < 3; k++)
								if (k != q) charchecked[k] = false;
							SDL_DestroyTexture(background1); SDL_DestroyTexture(background2);
							background1 = IMG_LoadTexture(renderer, background[pickedchar].c_str());
							background2 = IMG_LoadTexture(renderer, background[pickedchar].c_str());
						}
				}
		}
	}
}
void showMenu(SDL_Renderer* renderer, int n)
{
	helpopen = false;
	musicPlay("songs/theme.ogg");
	if (n == 1) welcomeAnimation(renderer);

	bool songPickerShow = false;
	SDL_Event e;

	while (songPickerShow == false)
	{
		SDL_RenderClear(renderer);
		showBackground(renderer, 1);
		imageShow(renderer, logo.c_str(), LOGO_POS_START_X, LOGO_POS_START_Y);
		imageShow(renderer, startbutton[pickedchar].c_str(), START_POS_START_X, START_POS_START_Y);
		imageShow(renderer, helpbutton[pickedchar].c_str(), HELP_POS_START_X, HELP_POS_START_Y);
		imageShow(renderer, quitbutton[pickedchar].c_str(), QUIT_POS_START_X, QUIT_POS_START_Y);
		if (helpopen == false) imageShow(renderer, charimage[pickedchar].c_str(), 532, 0);
		else
		{
			imageShow(renderer, helphover[pickedchar].c_str(), HELP_POS_START_X, HELP_POS_START_Y);
			for (int i = 0; i < 23; i++)
				textSet1(renderer, about[i], 24, 0, 1, 520, 88 + i * 26);
		}

		
		if (checkMouseHover(START_POS_START_X, START_POS_START_Y, START_POS_END_X, START_POS_END_Y) == true)
		{
			imageShow(renderer, starthover[pickedchar].c_str(), START_POS_START_X, START_POS_START_Y);
			if (Mix_Playing(-1) != 1) sfxPlay(1);
		}

		else if (checkMouseHover(HELP_POS_START_X, HELP_POS_START_Y, HELP_POS_END_X, HELP_POS_END_Y) == true)
		{
			imageShow(renderer, helphover[pickedchar].c_str(), HELP_POS_START_X, HELP_POS_START_Y);
			if (Mix_Playing(-1) != 1) sfxPlay(1);
		}
		else if (checkMouseHover(QUIT_POS_START_X, QUIT_POS_START_Y, QUIT_POS_END_X, QUIT_POS_END_Y) == true)
		{
			imageShow(renderer, quithover[pickedchar].c_str(), QUIT_POS_START_X, QUIT_POS_START_Y);
			if (Mix_Playing(-1) != 1) sfxPlay(1);
		}
		else
			Mix_HaltChannel(-1);

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) break;
			else if (e.type == SDL_MOUSEBUTTONDOWN) {

				if (e.button.button == SDL_BUTTON_LEFT)
					if (e.button.x > START_POS_START_X && e.button.y > START_POS_START_Y && e.button.x < START_POS_END_X && e.button.y < START_POS_END_Y)
					{
						int Mix_HaltMusic();
						sfxPlay(2);
						songPickerShow = true;
					}
					else if (e.button.x > QUIT_POS_START_X && e.button.y > QUIT_POS_START_Y && e.button.x < QUIT_POS_END_X && e.button.y < QUIT_POS_END_Y)
					{
						SDL_Quit();
					}
					else if (e.button.x > HELP_POS_START_X && e.button.y > HELP_POS_START_Y && e.button.x < HELP_POS_END_X && e.button.y < HELP_POS_END_Y)
					{
						if (helpopen == false)
						{
							helpopen = true;
					
						}
						else
						helpopen = false;
				
					}
			}
		}


		if (songPickerShow == true)
			songPicker(renderer);

		SDL_RenderPresent(renderer);
	}
}
