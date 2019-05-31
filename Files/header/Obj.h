#pragma once
#include <SDL.h>
#include <string>
#include "collision.h"
#include "Timer.h"
#include "animations.h"
using namespace std;

// 1 meter = 13 px


class Vector {
public:
	Vector();
	void NormalizeVector();
	int x, y;
	int mag;//newtons (1 newton -> 1 kg -> 1 km/s
	Vector* next = nullptr;
};

class Obj {
public:
	Obj();
	bool IsInView();
	void ChangeAnimation(const int ani[2],int tmpSpeed);
	const char* name = nullptr;
	SDL_Rect rect;
	string texName;
	Obj* next = nullptr;
	//physics
	int mass; //men -> 88 kg women -> 77 kg
	Vector* vectList = nullptr;
	//animation
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
