#pragma once
#include <SDL.h>
#include <SDL_image.h>
class game{
public:
	
	static 
private:
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static void RenderWindow();
	static void GameLoop();
	//static SDL_Texture* ImgLoad(char* path);
};

