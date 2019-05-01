#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_error.h>
#include <SDL_image.h>
#include "list.h"
#include "map.h"


Obj* objList; //might need to add a 'render this' bool to obj tho
texture* loadedTextures; // doesn't include the map textures
SDL_Renderer* renderer;
SDL_Window* window;
map* hub;
