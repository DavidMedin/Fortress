#include "../header/map.h"
extern texture* ImgLoad(const char* path);

room::room() {
	tileList = nullptr;
}

map::map(room* roomList) {
	//eventually, the map will be randomly generated and then find the necessry textures to use, so no input
	
	room* itr = roomList;
	do {

		itr = itr->next;
	} while (itr != nullptr);
}