#pragma once
#include <SDL.h>
#include <string>
using namespace std;


class Obj {
public:
	Obj();
	const char* name = nullptr;
	SDL_Rect rect;
	string texName;
	Obj* next = nullptr;
private:
	int relX, relY;

};

class Texture {
public:
	string texName = nullptr;
	SDL_Texture* tex = nullptr;
	Texture* next = nullptr;
};

class Tile : public Obj {
public:
	bool isWalkable = false;
	Tile(int x, int y);
	Tile();
};

