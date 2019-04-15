#include "../header/map.h"
extern texture* ImgLoad(const char* path);


map::map(texture* textureList) {
	//eventually, the map will be randomly generated and then find the necessry textures to use, so no input
	/*va_list args;
	va_start(args,paths);
	texture* pmt = list::AddNode<texture>(texList);
	pmt = ImgLoad(paths);
	const char* itr = va_arg(args,const char*);
	while (*itr != '.') {
		texture* tmp = list::AddNode<texture>(texList);
		tmp = ImgLoad(itr);
		va_arg(args, const char);
	}
	va_end(args);*/
	texList = textureList;
	roomList = nullptr;
}

room::room() {
	tileList = nullptr;
}
