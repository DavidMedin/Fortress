#include "../header/map.h"
using namespace std;
extern SDL_Texture* ImgLoad(const char* path);

map::map(const char* mapPath) {
	ifstream mapFile;
	mapFile.open(mapPath);
	//File formate for .map is (x,y,room,textureName) room starts at 0
	string input;
	while (!mapFile.eof()) {
		do { // X
			input += mapFile.get();
		} while (input.back() != ',');
		
		int dig = stoi(input); //numbers first with stoi
		Tile* tmpTile = new Tile;
		tmpTile->rect.x = dig;
		input.clear();
			//create a tile*, and populate it with x,y, and tex name (which will be processed),
			// when read the id, and if roomList is not null, find the room with the same id, if there is non,
			// then make one with that id, otherwise make one with that id
		do { // Y
			input += mapFile.get();
		} while (input.back() != ',');
		dig = stoi(input, nullptr);
		tmpTile->rect.y = dig;
		input.clear();

		do { // room id
			input += mapFile.get();
		} while (input.back() != ',');
		dig = stoi(input);
		//place here if fails
		input.clear();
		do{ // texture name for lookup
			input += mapFile.get();
		} while (input.back() != ';');
		input.pop_back(); //gets rid of the ;
		tmpTile->texName = input.c_str();
		input.clear();
		char boi = mapFile.get(); //this is for the newLine at the end of each line (duh)

		//dummy
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
			printf();
		}

	}
	
	mapFile.close();
	

}


room::room() {
	tileList = nullptr;
	//all of the tiles that are to be added to this list will have a standard size, constant
}