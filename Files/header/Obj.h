#pragma once
#include <SDL.h>
#include <string>
#include "collision.h"
using namespace std;


class Obj {
public:
	Obj();
	bool IsInView();
	const char* name = nullptr;
	SDL_Rect rect;
	string texName;
	Obj* next = nullptr;
private:
	int relX, relY;

};

class Texture {
public:
	string texName;
	SDL_Texture* tex = nullptr;
	Texture* next = nullptr;
};

class Tile : public Obj {
public:
	bool isWalkable = false;
	Tile(int x, int y);
	Tile();
};

class Actor : public Obj {
public: 
	Actor();
	float mass;
	bool hasGravity;
};

//force
//momentum
//acceleration
