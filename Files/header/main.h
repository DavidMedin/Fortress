#pragma once
#include <stdio.h>
#include <SDL.h>
#include <SDL_render.h>
#include <SDL_error.h>
#include <SDL_image.h>
#include "list.h"
#include "map.h"


Obj* actorList;
SDL_Texture* loadedTextures;
SDL_Renderer* renderer;
SDL_Window* window;
map* hub;