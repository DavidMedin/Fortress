#pragma once
#include <SDL.h>
#include <fstream>
#include "obj.h"
#include "list.h"

class room {
public:
	Tile* tileList = nullptr;
	room* next = nullptr;
	room();
};


class map {
public:
	Obj* texList = nullptr; // use the ->name in object for storing strings in lists
	room* roomList = nullptr;
	map(const char* mapPath);

};

