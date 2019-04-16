#include "../header/main.h"
//void RenderWindow();
//SDL_Texture* ImgLoad(char* path);

void RenderWindow();
SDL_Texture* ImgLoad(const char* path);



int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	loadedTextures = nullptr;
	room* roomList = nullptr;
	room* tmproom = list::AddNode<room>(roomList);
	Tile* tmp = list::AddNode<Tile>(tmproom->tileList);
	tmp->texName = "../Data/Tile.png";
	tmp->rect.x = 0;
	tmp->rect.y = 0;
	tmp->rect.w = 20;
	tmp->rect.h = 20;

	tmp = list::AddNode<Tile>(tmproom->tileList);
	tmp->texName = "../Data/Character.png";
	tmp->rect.x = 20;
	tmp->rect.y = 0;
	tmp->rect.w = 20;
	tmp->rect.h = 20;

	tmproom = list::AddNode<room>(roomList);
	tmp = list::AddNode<Tile>(tmproom->tileList);
	tmp->texName = "../Data/Tile.png";
	tmp->rect.x = 40;
	tmp->rect.y = 0;
	tmp->rect.w = 20;
	tmp->rect.h = 20;

	hub = new map(roomList);
	loadedTextures = nullptr;
	
	
	
	Tile* tileList = nullptr;
	list::AddNode<Tile>(tileList);
	list::AddNode<Tile>(tileList);
	Tile* itr = tileList;
	Tile* last = nullptr;
	do {
		last = itr;
		itr = (Tile*)itr->next;
	} while (itr->next != nullptr);

	while (1) {
		//game loop!!!
		RenderWindow();
		

	}
	SDL_Quit();
	return 0;
}

void RenderWindow() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 225);
	SDL_RenderClear(renderer);
	
	//whenever the player enteres the next 'map', then the current loadedtex will be trashed, and a new one will be genereated from the maps texList of strings.

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
