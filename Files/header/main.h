#pragma once
#include "render.h"
#include "Input.h"
#include "Timer.h"
#include "physics.h"


int offX = 0;
int offY = 0;
float scale = 0;

string editTexPath = "Data/Grass.png";

bool isEdit = true;
bool isTypeing = false;

 SDL_DisplayMode DM; // only really need for fullscreen mode

 Texture* loadedTextures; // doesn't include the map textures
 Obj* texLoadQueue;
 SDL_Renderer* renderer;
 SDL_Window* window;
 Map* hub;

 Map* targetMap;
 Room* targetRoom;

