#include <stdio.h>
#include <SDL.h>

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, NULL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 1, NULL);
	
	
	while (1) {
		SDL_SetRenderDrawColor(renderer,0, 0, 0, 255);
		SDL_RenderClear(renderer);


		

		SDL_RenderPresent(renderer);
	}

	return 0;
}