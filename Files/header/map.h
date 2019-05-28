#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>
#include <string>
#include <iostream>
#include "list.h"
class Room {
public:
	Tile* tileList = nullptr;
	Room* next = nullptr;
	int id = NULL;
	int height = NULL;
	int width = NULL;
	Room();
	void RecalcSize();
};


class Map {
public:
	Obj* texList = nullptr; // use the ->name in object for storing strings in lists
	Room* roomList = nullptr;
	Actor* actorList = nullptr;
	const char* path;
	Map(const char* mapPath);
	void AddTile(int x,int y,int room, const char* path);
	void AddActor(int x, int y, const char* path);
	void SaveMap();
};

