#include <SDL.h>
#include <SDL_mixer.h>

void initMedia();
void welcomeAnimation(SDL_Renderer* renderer);
void showUI(SDL_Renderer* renderer);
void showSongs(SDL_Renderer* renderer);
void showModes(SDL_Renderer* renderer, int* bpmin, float* speedin);
void showChars(SDL_Renderer* renderer);
void songPicker(SDL_Renderer* renderer);
void showMenu(SDL_Renderer* renderer, int n);
void showBackground(SDL_Renderer* renderer, int n);