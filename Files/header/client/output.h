#pragma once
#include <SDL.h>
#include <SDL_image.h>

class output {
public:
	static void start();

private:
	static SDL_Texture* ImgLoad(const char* path);
	static void GameLoop();
	static void RenderWindow();
};

