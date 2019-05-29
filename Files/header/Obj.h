#pragma once
#include <SDL.h>
#include <string>
#include "collision.h"
#include "Timer.h"
#define GUARD_SPEED 500
const int GUARD_IDLE[2]{ 1,4 }; 
using namespace std;


class Obj {
public:
	Obj();
	bool IsInView();
	void ChangeAnimation(const int ani[2],int tmpSpeed);
	const char* name = nullptr;
	SDL_Rect rect;
	string texName;
	Obj* next = nullptr;
	int frame = 1;
	Timer* frameTimer;
	int speed;
	int animation[2];
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
