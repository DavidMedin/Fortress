#pragma once
#include "render.h"
#include "Input.h"
#include "Timer.h"



int offX = 0;
int offY = 0;
float scale = 1;

string editTexPath = "Data/Grass.png";

bool isEdit = true;
bool isTypeing = false;

 SDL_DisplayMode DM; // only really need for fullscreen mode

 Obj* objList; //might need to add a 'render this' bool to obj tho
 Texture* loadedTextures; // doesn't include the map textures
 Obj* texLoadQueue;
 SDL_Renderer* renderer;
 SDL_Window* window;
 Map* hub;

 Map* targetMap;
 Room* targetRoom;

