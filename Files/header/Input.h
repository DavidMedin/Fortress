#pragma once
#include "Data.h"
namespace Input {
	int isDownOnce(const Uint8* state, SDL_Scancode current);
	int isDownOnceMouse(int* x, int* y, int state);
	int NearestTile(int x, int y, bool round);
}
