#include <SDL.h>
#include <SDL_mixer.h>

extern bool songchecked[10];
extern bool modechecked[3];
extern bool charchecked[3];

extern int pickedsong;
extern int pickedchar;

extern bool welcomecheck;
extern int backgroundPos;

void initMedia();
void songPicker(SDL_Renderer* renderer);
void showMenu(SDL_Renderer* renderer, int n);
void showBackground(SDL_Renderer* renderer, int n);