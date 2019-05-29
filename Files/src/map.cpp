#include "../header/map.h"

using namespace std;
extern SDL_Texture* ImgLoad(const char* path);

// standard black size is 32
void Map::AddActor(int x, int y, const char* path) {
	list::AddNode<Actor>(&actorList);
	actorList->rect.x = x;
	actorList->rect.y = y;
	actorList->texName = path;
	SDL_Surface* surf = IMG_Load(path);
	actorList->rect.w = surf->w;
	actorList->rect.h = surf->h;
	SDL_FreeSurface(surf);
}

Map::Map(const char* mapPath) {
	path = mapPath;
	ifstream mapFile;
	mapFile.open(mapPath);
	//File formate for .map is (x,y,room,textureName) room starts at 0
	string input;
	bool type = true;
	while (!mapFile.eof()) {
		type = true;
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
		input.pop_back();
		if (isdigit((int)input[0])) {
			dig = stoi(input);
			input.clear();
			type = false;
		}
		input.clear();
		//do {// 'tile' type
		//	input += mapFile.get();
		//} while (input.back() != ',');
		//input.pop_back(); //gets rid of the ','
		//type = input;
		//input.clear();
		do{ // texture name for lookup
			input += mapFile.get();
		} while (input.back() != ';');
		input.pop_back(); //gets rid of the ;
		tmpTile->texName = input;
		//########################
		if (input == "Data/Guard.png") {
			tmpTile->rect.w = 26;
			tmpTile->rect.h = 24;
			tmpTile->speed = GUARD_SPEED;
			memcpy(tmpTile->animation, GUARD_IDLE,sizeof(int)*2);
		}
		else {
			SDL_Surface* surf = IMG_Load(input.c_str());
			tmpTile->rect.w = surf->w;
			tmpTile->rect.h = surf->h;
			SDL_FreeSurface(surf);
		}
		
		if (type == false) {
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
			
		}
		else if (type == true) {
			AddActor(tmpTile->rect.x, tmpTile->rect.y, tmpTile->texName.c_str());
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
						if (texItr == nullptr || texItr->texName == tileItr->texName) {
							break;
						}
						texItr = texItr->next;
					} while (texItr != nullptr);
					if (texItr == nullptr) {
						list::AddNode<Obj>(&texList);
						texList->texName = tileItr->texName;
					}
					tileItr = (Tile*)tileItr->next;
				} while (tileItr != nullptr);
				roomItr = roomItr->next;
			} while (roomItr != nullptr);


			Actor* jace = actorList;
			if (jace != nullptr) {
				do {
					Obj* texItr = texList;
					do {
						if (texItr == nullptr || texItr->texName == jace->texName) {
							break;
						}
						texItr = texItr->next;
					} while (texItr != nullptr);
					if (texItr == nullptr) {
						list::AddNode<Obj>(&texList);
						texList->texName = jace->texName;
					}
					jace = (Actor*)jace->next;
				} while (jace != nullptr);
			}

			roomItr = roomList;
			do {
				roomItr->RecalcSize();
				roomItr = roomItr->next;
			} while (roomItr != nullptr);
		}


}

void Map::AddTile(int x, int y, int room, const char* path) {
	if (path != nullptr) {
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

		//###########################
		if (path == "Data/Guard.png") {
			targetRoom->tileList->rect.w = 26;
			targetRoom->tileList->rect.h = 24;
			targetRoom->tileList->speed = GUARD_SPEED;
			memcpy(targetRoom->tileList->animation, GUARD_IDLE, sizeof(int) * 2);
		}
		else {
			SDL_Surface* surf = IMG_Load(path);
			targetRoom->tileList->rect.w = surf->w;
			targetRoom->tileList->rect.h = surf->h;
			SDL_FreeSurface(surf);
		}
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
		if (tileItr != nullptr) {
			do {
			output.write(to_string(tileItr->rect.x).c_str(), to_string(tileItr->rect.x).size());
			output.write(",",1);
			output.write(to_string(tileItr->rect.y).c_str(), to_string(tileItr->rect.y).size());
			output.write(",", 1);
			output.write(to_string(roomItr->id).c_str(), to_string(roomItr->id).size());
			output.write(",", 1);
			output.write(tileItr->texName.c_str(), tileItr->texName.size());
			output.write(";", 1);
			if (roomItr->next != nullptr || tileItr->next != nullptr || actorList != nullptr) {
				output.write("\n",1);
			}
			tileItr = (Tile*)tileItr->next;
		} while (tileItr != nullptr);
		}
		roomItr = roomItr->next;
	} while (roomItr != nullptr);
	Actor* actTmp = actorList;
	if (actTmp != nullptr) {
		do {
			output.write(to_string(actorList->rect.x).c_str(), to_string(actorList->rect.x).size());
			output.write(",", 1);
			output.write(to_string(actorList->rect.y).c_str(), to_string(actorList->rect.y).size());
			output.write(",", 1);
			output.write("a", sizeof(char));
			output.write(",", 1);
			output.write(actorList->texName.c_str(), actorList->texName.size());
			output.write(";", 1);
			if (actorList->next != nullptr) {
				output.write("\n", 1);
			}
			actTmp = (Actor*)actTmp->next;
		} while (actTmp != nullptr);
	}
	output.close();
}

