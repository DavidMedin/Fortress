#include "../header/collision.h"

bool collision::BoxPointCollision(SDL_Rect* rect, SDL_Point* point) {
	int x1 = rect->x;
	int y1 = rect->y;
	int x2 = rect->x + rect->w;
	int y2 = rect->y + rect->h;
	if (point->x > x1 && point->y > y1 && point->x < x2 && point->y < y2) {
		return true;
	}
	else {
		return false;
	}
}
bool collision::HalfDoubleBoxCollision(SDL_Rect* rect1, SDL_Rect* rect2) {
	int x1 = rect1->x;
	int y1 = rect1->y;
	int x2 = rect1->x + rect1->w;
	int y2 = rect1->y + rect1->h;
	for (int i = 0; i < 4; i++) {
		int pointX;
		int pointY;
		switch (i) {
		case 0: 
			pointX = rect2->x;
			pointY = rect2->y;
			break;
		case 1: 
			pointX = rect2->x + rect2->w;
			pointY = rect2->y;
			break;
		case 2:
			pointX = rect2->x;
			pointY = rect2->h + rect2->y;
			break;
		case 3:
			pointX = rect2->x + rect2->w;
			pointY = rect2->h + rect2->y;
			break;
		}
		if (pointX > x1 && pointY > y1 && pointX < x2 && pointY < y2) {
			return true;
		}
		
	}
	return false;
}

bool collision::DoubleBoxCollision(SDL_Rect* rect1, SDL_Rect* rect2) {
	if (HalfDoubleBoxCollision(rect1, rect2) || HalfDoubleBoxCollision(rect2, rect1)) {
		return true;
	}
	else return false;
}

