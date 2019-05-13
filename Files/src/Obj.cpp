#include "../header/Obj.h"

Obj::Obj() {
	name = "here";
	rect = { 0 };
	relX = 0;
	relY = 0;
}

Tile::Tile(int x, int y) {
	isWalkable = true;
	rect.x = x;
	rect.y = y;
}
Tile::Tile() {

}