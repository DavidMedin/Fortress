#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_error.h>
#include <SDL_video.h>
#include <conio.h>
#include <string>
#include "map.h"
#define INIT_WIDTH 900
#define INIT_HEIGHT 600
#define BASE_SIZE 8


extern int offX;
extern int offY;
extern float scale;

extern SDL_DisplayMode DM; // only really need for fullscreen mode

extern Obj* objList; //might need to add a 'render this' bool to obj tho
extern Texture* loadedTextures; // doesn't include the map textures
extern Obj* texLoadQueue;
extern SDL_Renderer* renderer;
extern SDL_Window* window;
extern Map* hub;

extern string editTexPath;

extern Map* targetMap;
extern Room* targetRoom;

extern bool isEdit;
extern bool isTypeing;
