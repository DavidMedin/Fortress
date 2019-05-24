#include "../header/map.h"
using namespace std;
extern SDL_Texture* ImgLoad(const char* path);

// standard black size is 32


Map::Map(const char* mapPath) {
	path = mapPath;
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
		printf("%s\n", input.c_str());
		SDL_Surface* surf = IMG_Load(input.c_str());
		tmpTile->rect.w = surf->w;
		tmpTile->rect.h = surf->h;
		SDL_FreeSurface(surf);
		if (roomList != nullptr) {
			Room* itr = roomList;
			do {
				if (itr->id == dig) {
					list::AddNode<Tile>(&itr->tileList);
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
			Room* tmpRoom = list::AddNode<Room>(&roomList);
			tmpRoom->id = dig;
			list::AddNode<Tile>(&tmpRoom->tileList);
			Tile* tmpNext = (Tile*)roomList->tileList->next;
			*roomList->tileList = *tmpTile;
			roomList->tileList->next = tmpNext;		
		}
		input.clear();
		char trash = mapFile.get(); //this is for the newLine at the end of each line (duh)
	}
	mapFile.close();
	//map will need a complete list of unique texture paths
	if (roomList == nullptr) {
		printf("map.txt is empty\n");
	}
	else {
		// add image paths to texList
		Room* roomItr = roomList;
		do {
			Tile* tileItr = roomItr->tileList;
			do {
				Obj* texItr = texList;
				do {
					if (texItr == nullptr) {
						list::AddNode<Obj>(&texList);
						texList->texName = tileItr->texName.c_str();
						break;
					}
					if (!strcmp(texItr->texName.c_str(),tileItr->texName.c_str())) {
						break;
					}
					texItr = texItr->next;
					if (texItr == nullptr) {
						list::AddNode<Obj>(&texList);
						texList->texName = tileItr->texName.c_str();
					}
				} while (texItr != nullptr);
				tileItr = (Tile*)tileItr->next;
			} while (tileItr != nullptr);
			roomItr = roomItr->next;
		} while (roomItr != nullptr);

		roomItr = roomList;
		do {
			roomItr->RecalcSize();
			roomItr = roomItr->next;
		} while (roomItr != nullptr);
	}
	

}

void Map::AddTile(int x, int y, int room, const char* path) {
	Room* targetRoom = nullptr;
	Room* tmpRoom = roomList;
	do { // iterates through the rooms and find the maching id
		if (tmpRoom->id == room) {
			targetRoom = tmpRoom;
			break;
		}
		tmpRoom = tmpRoom->next;
	} while (tmpRoom != nullptr);
	if (targetRoom == nullptr) { // if it got through the iterator, and no match, then make a new room
		targetRoom = list::AddNode<Room>(&roomList);
		targetRoom->id = room;
	}
	list::AddNode<Tile>(&targetRoom->tileList); // creates a new tile in the room
	targetRoom->tileList->texName = path;
	targetRoom->tileList->rect.x = x;
	targetRoom->tileList->rect.y = y;
	SDL_Surface* surf = IMG_Load(path);
	targetRoom->tileList->rect.w = surf->w;
	targetRoom->tileList->rect.h = surf->h;
	SDL_FreeSurface(surf);
	Obj* texItr = texList;
	do {
		if (texItr->texName == path) {
			break;
		}
		texItr = texItr->next;
	} while (texItr != nullptr);
	if (texItr == nullptr) {
		list::AddNode<Obj>(&texList);
		texList->texName = path;
	}
}

Room::Room() {

}

void Room::RecalcSize() {
	int maxX = NULL;
	int maxY = NULL;
	int minX = NULL;
	int minY = NULL;
	Tile* tileItr = tileList;
	do {
		if (tileItr == tileList) {
			maxX = tileItr->rect.x + tileItr->rect.w;
			maxY = tileItr->rect.y + tileItr->rect.h;
			minX = tileItr->rect.x;
			minY = tileItr->rect.y;
		}
		if (tileItr->rect.x < minX) {
			minX = tileItr->rect.x;
		}
		else if (tileItr->rect.x + tileItr->rect.w > maxX) {
			maxX = tileItr->rect.x + tileItr->rect.w;
		}
		if (tileItr->rect.y < minY) {
			minY = tileItr->rect.y;
		}
		else if (tileItr->rect.y + tileItr->rect.h > maxY) {
			maxY = tileItr->rect.y + tileItr->rect.h;
		}
		tileItr = (Tile*)tileItr->next;
	} while (tileItr != nullptr);
	width = maxX - minX;
	height = maxY - minY;
}

void Map::SaveMap() {
	ofstream output;
	output.open(path, ofstream::out | ofstream::trunc);
	Room* roomItr = roomList;
	do {
		Tile* tileItr = roomItr->tileList;
		do {
			output.write(to_string(tileItr->rect.x).c_str(), to_string(tileItr->rect.x).size());
			output.write(",",1);
			output.write(to_string(tileItr->rect.y).c_str(), to_string(tileItr->rect.y).size());
			output.write(",", 1);
			output.write(to_string(roomItr->id).c_str(), to_string(roomItr->id).size());
			output.write(",", 1);
			output.write(tileItr->texName.c_str(), tileItr->texName.size());
			output.write(";", 1);
			if (roomItr->next != nullptr || tileItr->next != nullptr) {
				output.write("\n",1);
			}
			tileItr = (Tile*)tileItr->next;
		} while (tileItr != nullptr);

		roomItr = roomItr->next;
	} while (roomItr != nullptr);
	output.close();
}