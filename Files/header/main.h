#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_error.h>
#include <SDL_video.h>
#include <conio.h>
//#include <SDL_image.h>
#include "list.h"
#include "map.h"
#include "Timer.h"
#include "Keyboard.h"
#define INIT_WIDTH 900
#define INIT_HEIGHT 600
#define BASE_SIZE 32



int offX = 0;
int offY = 0;
float scale = 1;

SDL_DisplayMode DM; // only really need for fullscreen mode

Obj* objList; //might need to add a 'render this' bool to obj tho
Texture* loadedTextures; // doesn't include the map textures
Texture* mapLoadTexes;
SDL_Renderer* renderer;
SDL_Window* window;
Map* hub;

Map* targetMap;
Room* targetRoom;

bool isEdit = true;