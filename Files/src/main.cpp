#include "../header/main.h"
#include <string>
//void RenderWindow();
//SDL_Texture* ImgLoad(char* path);

void RenderWindow();
SDL_Texture* ImgLoad(const char* path);
map* targetMap;


int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_GetCurrentDisplayMode(0, &DM);

	loadedTextures = nullptr;
	mapLoadTexes = nullptr;
	hub = new map("../Data/map.map");
	targetMap = hub;
	/*room* roomList = nullptr;
	room* tmpRoom = list::AddNode<room>(roomList);
	Tile* tmpTile = list::AddNode<Tile>(tmpRoom->tileList);
	Tile* boi = new Tile;
	boi->texName = "boi";
	boi->isWalkable = true;
	*tmpTile = *boi;
	*/




	while (1) {
		//game loop!!!
		RenderWindow();
		

	}
	SDL_Quit();
	return 0;
}

void RenderWindow() {	
	Room* roomItr = targetMap->roomList;
	do {
		Tile* tileItr = roomItr->tileList;
		do {
			//add conditional that if tile is within the 'camera' view, then add to list
			texture* mapTexItr = mapLoadTexes;
			do {
				
				//maybe make a function for populating a list of unique items of a specific type

				mapTexItr = mapTexItr->next;
			} while (mapTexItr != nullptr);
			tileItr = (Tile*)tileItr->next;
		} while (tileItr != nullptr);
		roomItr = roomItr->next;
	} while (roomItr != nullptr);
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
	SDL_RenderClear(renderer);
	
	//map rendering
	// w / roomW * ScreenWidth
	SDL_Rect tmpRect;
	roomItr = targetMap->roomList;
	do {
		Tile* tileItr = roomItr->tileList;
		do {
			tmpRect = tileItr->rect;
			tmpRect.w = tileItr->rect.w / roomItr->width * DM.w;
			tmpRect.h = tileItr->rect.h / roomItr->height * DM.h;
			tmpRect.x = tileItr->rect.x;
			tmpRect.y = tileItr->rect.y;
			SDL_Texture* tmpTex = 
			SDL_RenderCopy(renderer,/*texture*/, NULL, &tmpRect);
			tileItr = (Tile*)tileItr->next;
		} while (tileItr != nullptr);
		roomItr = roomItr->next;
	} while (roomItr != nullptr);
	
	SDL_RenderPresent(renderer);
}

SDL_Texture* ImgLoad(const char* path) {
	SDL_Surface* surface = IMG_Load(path);
	if (surface == NULL) {
		printf("%s, did you forget the zlib.dll?\n", IMG_GetError());
	}
	SDL_Texture* tmp = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return tmp;	
}
