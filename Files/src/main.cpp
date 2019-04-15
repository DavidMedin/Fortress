#include "../header/main.h"
//void RenderWindow();
//SDL_Texture* ImgLoad(char* path);

void RenderWindow();
texture* ImgLoad(char* path);

void test(const char* args...) {
	va_list argv;
	va_start(argv, args);
	printf("%s\n", args);
	char* itr = va_arg(argv,char*);
	while (itr != "\0") {
		printf("%s\n", itr);
		itr = va_arg(argv, char*);
	}
	va_end(argv);
}


int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	actorList = nullptr;
	list::AddNode<Obj>(actorList);
	loadedTextures = nullptr;
	//hub = new map("../Data/character.png");
	//SDL_Surface* boi = IMG_Load("../Data/character.png");
	//texture* boi = ImgLoad("../Data/Character.png")
	//test("boi oh boi","hello there","oh, but I am not done yet","\0");
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


	SDL_RenderPresent(renderer);
}

texture* ImgLoad(const char* path) {
	texture* tmp = new texture;
	SDL_Surface* surface = IMG_Load(path);
	/*if ((surface = IMG_Load(path)) < 0) {
		printf("error loading image: %s\n", IMG_GetError()); 
	}*/
	tmp->tex = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return tmp;	
}
