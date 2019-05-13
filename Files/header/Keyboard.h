#pragma once
#include <SDL.h>
int isDownOnce(const Uint8* state,SDL_Scancode current);
int isDownOnceMouse(int* x,int* y,int state);