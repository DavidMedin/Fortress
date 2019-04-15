#include "../header/game.h"

void game::Start() {

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
	renderer = SDL_CreateRenderer(window, 1, 0);

	GameLoop();
}


