#include <SDL.h>
#include <iostream>;
#include <string>;

using namespace std;

void logSDLError(std::ostream& os, const std::string& msg, bool fatal);
void initSDL(SDL_Window*& window, SDL_Renderer*& renderer, const int SCREEN_WIDTH, int SCREEN_HEIGHT, const string &WINDOW_TITLE);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
int randomSpawn();