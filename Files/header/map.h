#pragma once
#include <SDL.h>
#include "obj.h"
#include "list.h"

class room {
public:
	Tile* tileList = nullptr;
	room();
};


class map {
public:
	texture* texList = nullptr;
	room* roomList = nullptr;
	map(texture* textureList);
};

