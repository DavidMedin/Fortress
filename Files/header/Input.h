#pragma once
#include <SDL.h>
#include "Data.h"
#include "Timer.h"
#include "image.h"
namespace Input {
	void CheckInput();
	int isDownOnceMouse(int* x, int* y, int state);
	int NearestTile(int x, int y, bool round);
}
