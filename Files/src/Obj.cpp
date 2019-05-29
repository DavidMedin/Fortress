#include "../header/Obj.h"

Obj::Obj() {
	name = "here";
	rect = { 0 };
	frameTimer = new Timer();
}
bool Obj::IsInView() {
	extern SDL_Window* window;
	extern int offX;
	extern int offY;
	extern float scale;
	SDL_Rect tmprect;
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	tmprect.w = (int)((float)w / scale);
	tmprect.h = (int)((float)h / scale);
	tmprect.x = offX - ((int)((float)w / scale) / 2); // real to virtual
	tmprect.y = offY - ((int)((float)h / scale) / 2);
	return collision::DoubleBoxCollision(&tmprect, &rect);
}
void Obj::ChangeAnimation(const int ani[2], int tmpSpeed) {
	memcpy(animation, ani, sizeof(int) * 2);
	speed = tmpSpeed;
}

Tile::Tile(int x, int y) {
	isWalkable = true;
	rect.x = x;
	rect.y = y;
}
Tile::Tile() {

}

Actor::Actor() {

}