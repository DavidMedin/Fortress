#include "../header/map.h"
using namespace std;
extern SDL_Texture* ImgLoad(const char* path);

map::map(const char* mapPath) {
	ifstream mapFile;
	mapFile.open(mapPath);
	//File formate for .map is (x,y,room,textureName,(optional)NextRoomID ) room starts at 0
	string input;
	while (!mapFile.eof()) {
		do {
			input += mapFile.get();
		} while (input.back() != ',');
		int dig = stoi(input, nullptr, 0);
		Tile* tmpTile;
		tmpTile->rect.x = dig;
			//create a tile*, and populate it with x,y, and tex name (which will be processed),
			// when read the id, and if roomList is not null, find the room with the same id, if there is non,
			// then make one with that id, otherwise make one with that id
		do {
			input += mapFile.get();
		} while (input.back() != ',');
		dig = stoi(input, nullptr, 0);
		tmpTile->rect.y = dig;
		do {
			input += mapFile.get();
		} while (input.back() != ',');
		dig = stoi(input, nullptr, 0);
		if (roomList != nullptr) {
			room* itr = roomList;
			do {
				if (itr->id == dig) {
					Tile* temperTile = list::AddNode<Tile>(itr->tileList);
					temperTile = tmpTile;
					break;
				}
				itr = itr->next;
			} while (itr != nullptr);
			if (itr == nullptr) {
				goto gelse;
			}
		}
		else {
		gelse:;
			room* tmpRoom = list::AddNode<room>(roomList);
			Tile* temperTile = list::AddNode<Tile>(tmpRoom->tileList);
			temperTile = tmpTile;
		}
		mapFile.get(); //this is for the \n at the end of each line
	}
	mapFile.close();

}


room::room() {
	tileList = nullptr;
	//all of the tiles that are to be added to this list will have a standard size, constant
}