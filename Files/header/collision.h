#pragma once
#include <SDL.h>

namespace collision {
	bool BoxPointCollision(SDL_Rect* rect,SDL_Point* point);
	bool HalfDoubleBoxCollision(SDL_Rect* rect1, SDL_Rect* rect2);
	bool DoubleBoxCollision(SDL_Rect* rect1, SDL_Rect* rect2);
};