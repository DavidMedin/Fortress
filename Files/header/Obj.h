#pragma once
#include <SDL.h>

class texture {
public:
	SDL_Texture* tex = nullptr;
	const char* texName = NULL;
	texture* next = nullptr;
};

class Obj {
public:
	Obj();
	const char* name = nullptr;
	SDL_Rect rect;
	const char* texName = nullptr;
	Obj* next = nullptr;
private:
	int relX, relY;

};

class Tile : public Obj {
public:
	bool isWalkable;
	Tile();
};

