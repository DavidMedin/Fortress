#include "../header/main.h"
#include "../header/client/output.h"
//
//struct texture {
//	SDL_Texture* imgTexture;
//	SDL_Rect rect;
//};
//

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, NULL);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 1, NULL);

	output::start();
	
	return 0;
}