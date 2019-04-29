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
		input.clear();
		do{ // texture name for lookup
			input += mapFile.get();
		} while (input.back() != ';');
		input.pop_back(); //gets rid of the ;
		tmpTile->texName = input;

		if (roomList != nullptr) {
			room* itr = roomList;
			do {
				if (itr->id == dig) {
					list::AddNode<Tile>(itr->tileList);
					Tile* tmpNext = (Tile*)roomList->tileList->next;
					*roomList->tileList = *tmpTile;
					roomList->tileList->next = tmpNext;
					break;
				}
				itr = itr->next;
			} while (itr != nullptr);
			if (itr == nullptr) {
				goto gelse;
			}
		}
		else { //this is if there is not a room with the specified id, or if there is no rooms in roomList
		gelse:;
			room* tmpRoom = list::AddNode<room>(roomList);
			tmpRoom->id = dig;
			list::AddNode<Tile>(tmpRoom->tileList);
			Tile* tmpNext = (Tile*)roomList->tileList->next;
			*roomList->tileList = *tmpTile;
			roomList->tileList->next = tmpNext;
		}
		input.clear();
		char boi = mapFile.get(); //this is for the newLine at the end of each line (duh)
	}
	mapFile.close();
	//map will need a complete list of unique texture paths
	if (roomList == nullptr) {
		printf("map.txt is empty\n");
	}
	else {
		room* roomItr = roomList;
		do {
			Tile* tileItr = roomItr->tileList;
			do {// stuck in this loop
				Obj* texItr = texList;
				do {
					if (texItr == nullptr) {
						list::AddNode<Obj>(texList);
						texList->texName = tileItr->texName.c_str();
						break;
					}
					if (!strcmp(texItr->texName.c_str(),tileItr->texName.c_str())) {
						break;
					}
					texItr = texItr->next;
					if (texItr == nullptr) {
						list::AddNode<Obj>(texList);
						texList->texName = tileItr->texName.c_str();
					}
				} while (texItr != nullptr);
				tileItr = (Tile*)tileItr->next;
			} while (tileItr != nullptr);
			roomItr = roomItr->next;
		} while (roomItr != nullptr);
	}
}


room::room() {

}