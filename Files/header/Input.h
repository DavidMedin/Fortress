#pragma once
#include <SDL.h>
namespace Input {
	int isDownOnce(const Uint8* state, SDL_Scancode current);
	int isDownOnceMouse(int* x, int* y, int state);
}
