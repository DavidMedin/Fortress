#include "../header/map.h"
using namespace std;
extern SDL_Texture* ImgLoad(const char* path);

map::map(const char* mapPath) {
	ifstream mapFile;
	mapFile.open(mapPath);
	//File formate for .map is (x,y,room,textureName) room starts at 0
	while (!mapFile.eof()) {
		char input; //maybe make std::string instead
	}
	mapFile.close();
	roomList = nullptr;
}


room::room() {
	tileList = nullptr;
	//all of the tiles that are to be added to this list will have a standard size, constant
}