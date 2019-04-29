#include "../header/main.h"
#include <string>
//void RenderWindow();
//SDL_Texture* ImgLoad(char* path);

void RenderWindow();
SDL_Texture* ImgLoad(const char* path);



int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	

	actorList = nullptr;
	loadedTextures = nullptr;
	hub = new map("../Data/map.txt");
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
	Obj* uniqTex = hub->texList;
	do {// this constructs the loaded texture list
		texture* loadItr = loadedTextures;
		do {
			if (loadItr == nullptr) {
				list::AddNode<texture>(loadedTextures);
				loadedTextures->texName = new Obj();
				loadedTextures->texName->texName = uniqTex->texName;
				loadedTextures->tex = ImgLoad(uniqTex->texName.c_str());
				break;
			}
			if (uniqTex->texName == loadItr->texName->texName) {
				break;
			}
			loadItr = loadItr->next;
			if (loadItr == nullptr) {
				list::AddNode<texture>(loadedTextures);
				loadedTextures->texName = new Obj();
				loadedTextures->texName->texName = uniqTex->texName;
				loadedTextures->tex = ImgLoad(uniqTex->texName.c_str());
			}
		} while (loadItr != nullptr);
		uniqTex = uniqTex->next;
	} while (uniqTex != nullptr);

	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
	SDL_RenderClear(renderer);
	



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
