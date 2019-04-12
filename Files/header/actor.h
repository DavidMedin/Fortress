#pragma once
#include <SDL.h>
#include <SDL_image.h>

class actor{
public:
	SDL_Texture* actorTexture;
};

class character : public actor {
public:
	character();
};