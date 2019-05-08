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
	Obj* texItr = targetMap->texList;
	do{
		Texture* mapLoadItr = mapLoadTexes;
		if (mapLoadTexes != nullptr) {
			do {
				if (mapLoadTexes->texName->texName == texItr->texName) {
					break;
				}
				mapLoadItr = mapLoadItr->next;
			} while (mapLoadItr != nullptr);
		}
		if (mapLoadItr == nullptr) {
			list::AddNode<Texture>(mapLoadTexes);
			mapLoadTexes->texName = new Obj();
			mapLoadTexes->texName->texName = texItr->texName;
			mapLoadTexes->tex = ImgLoad(texItr->texName.c_str());
		}

		texItr = texItr->next;
	}while (texItr != nullptr);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
	SDL_RenderClear(renderer);
	
	//map rendering
	// w / roomW * ScreenWidth
	SDL_Rect tmpRect;
	Room* roomItr = targetMap->roomList;
	do {
		Tile* tileItr = roomItr->tileList;
		do {
			SDL_Texture* tmpTex = nullptr;
			Texture* texLoop = mapLoadTexes;
			do {
				if (texLoop->texName->texName == tileItr->texName) {
					tmpTex = texLoop->tex;
					break;
				}
				texLoop = texLoop->next;
			} while (texLoop != nullptr);
			int w, h;
			SDL_QueryTexture(tmpTex, NULL, NULL, &w, &h);
			tmpRect = tileItr->rect;
			int targetSize = w < h ? h : w;
			// screen width / w
			tmpRect.w = DM.w / roomItr->width;
			tmpRect.h = DM.h / roomItr->height;
			tmpRect.x = tileItr->rect.x * targetSize;
			tmpRect.y = tileItr->rect.y * targetSize;
			SDL_RenderCopy(renderer, tmpTex, NULL, &tmpRect);
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
