#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_error.h>
#include <SDL_image.h>
#include "list.h"
#include "map.h"


Obj* actorList;
Obj* loadTexQue; // get rid of the map texList, this is a global texList
texture* loadedTextures;
SDL_Renderer* renderer;
SDL_Window* window;
map* hub;
