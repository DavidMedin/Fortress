#pragma once
#include <SDL.h>

class collision {
public:
	static bool BoxPointCollision(SDL_Rect* rect,SDL_Point* point);
	static bool HalfDoubleBoxCollision(SDL_Rect* rect1, SDL_Rect* rect2);
	static bool DoubleBoxCollision(SDL_Rect* rect1, SDL_Rect* rect2);
};