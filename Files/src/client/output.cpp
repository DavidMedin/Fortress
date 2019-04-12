#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../../header/client/output.h"
//temp
#include "../../header/main.h"

//public
void output::start() {
	texs[0] = output::ImgLoad("../Data/character.png");
	//mainChar = new character();

	GameLoop();
}

void output::GameLoop() {
	RenderWindow();
}

//private
void output::RenderWindow() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	

	SDL_RenderPresent(renderer);
}

SDL_Texture* output::ImgLoad(const char* path) {
	SDL_Surface* surface = IMG_Load(path);
	SDL_Texture* tmpTex = SDL_CreateTextureFromSurface(renderer, surface);
	free(surface);
	return tmpTex;
}