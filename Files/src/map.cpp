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
			Room* itr = roomList;
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
			Room* tmpRoom = list::AddNode<Room>(roomList);
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
		Room* roomItr = roomList;
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
		roomItr = roomList;
		do {
			int maxX = NULL;
			int maxY = NULL;
			int minX = NULL;
			int minY = NULL;
			Tile* tileItr = roomItr->tileList;
			do {
				if (tileItr == roomItr->tileList) {
					maxX = tileItr->rect.x;
					maxY = tileItr->rect.y;
					minX = tileItr->rect.x;
					minY = tileItr->rect.y;
				}
				if (tileItr->rect.x < minX) {
					minX = tileItr->rect.x;
				}
				else if (tileItr->rect.x > maxX) {
					maxX = tileItr->rect.x;
				}
				if (tileItr->rect.y < minY) {
					minY = tileItr->rect.y;
				}
				else if (tileItr->rect.y > maxY) {
					maxY = tileItr->rect.y;
				}
				tileItr = (Tile*)tileItr->next;
			} while (tileItr != nullptr);
			roomItr->width = maxX - minX;
			roomItr->height = maxY - minY;
			if (roomItr->width <= 0) roomItr->width = 1;
			if (roomItr->height <= 0) roomItr->height = 1;
			roomItr = roomItr->next;
		} while (roomItr != nullptr);
	}
	

}


Room::Room() {

}