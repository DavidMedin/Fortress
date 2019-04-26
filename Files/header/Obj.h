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
	SDL_Rect rect;
	const char* texName;
	Obj* next = nullptr;
private:
	int relX, relY;

};

class Tile : public Obj {
public:
	bool isWalkable;
	//Tile(int x, int y, int scale);
	Tile();
};

