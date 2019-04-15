#include "../header/map.h"
extern texture* ImgLoad(const char* path);


map::map(const char* paths...) {
	va_list args;
	va_start(args,paths);
	texture* pmt = list::AddNode<texture>(texList);
	pmt = ImgLoad(paths);
	const char* itr = va_arg(args,const char*);
	while (itr != "\0") {
		texture* tmp = list::AddNode<texture>(texList);
		tmp = ImgLoad(itr);
		va_arg(args, const char);
	}
	va_end(args);
	roomList = nullptr;
}

room::room() {
	tileList = nullptr;
}
