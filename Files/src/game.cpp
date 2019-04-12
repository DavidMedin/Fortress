#include "../header/game.h"
//#include "../header/main.h"
//#include <SDL.h>
//#include <SDL_image.h>
void game::Start() {

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
	renderer = SDL_CreateRenderer(window, 1, 0);

	GameLoop();
}
void game::RenderWindow() {
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
void game::GameLoop() {
	while (1) {
		RenderWindow();
	}
}
//SDL_Texture* game::ImgLoad(char* path) {
//	SDL_Surface* surface = IMG_Load(path);
//	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
//	free(surface);
//	return tex;	
//}