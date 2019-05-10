#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <string>
#include <iostream>
#include "obj.h"
#include "list.h"
class Room {
public:
	Tile* tileList = nullptr;
	Room* next = nullptr;
	int id = NULL;
	int height = NULL;
	int width = NULL;
	Room();
};


class Map {
public:
	Obj* texList = nullptr; // use the ->name in object for storing strings in lists
	Room* roomList = nullptr;
	Map(const char* mapPath);

};

