#pragma once
#include <SDL.h>

class texture {
public:
	SDL_Texture* tex = nullptr;
	texture* next = nullptr;
};

class Obj {
public:
	Obj();
	const char* name;
	int x, y;
	texture* tex = nullptr;
	Obj* next = nullptr;
private:
	int relX, relY;

};

class Tile : public Obj {
public:
	bool isWalkable;
	Tile();
};

