#include "../header/main.h"

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, INIT_WIDTH, INIT_HEIGHT, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_GetCurrentDisplayMode(0, &DM);
	
	loadedTextures = nullptr;
	texLoadQueue = nullptr;
	hub = new Map("Data/map.map");
	targetMap = hub;
	targetRoom = targetMap->roomList;
	
	while (1) {

		//game loop!!!	
		Input::CheckInput();
		if (isEdit) {
			int x, y;
			if (Input::isDownOnceMouse(&x, &y,SDL_BUTTON_LEFT) == 1) {
				hub->AddTile(Input::NearestTile(x,NULL,true), Input::NearestTile(NULL,y,true), 0, editTexPath.c_str());
				targetMap->SaveMap();
			}
			else if (Input::isDownOnceMouse(&x, &y, SDL_BUTTON_RIGHT) == 1) {
				Room* roomItr = hub->roomList;
				do {
					Tile* tileItr = roomItr->tileList;
					do {
						if (tileItr->rect.x == Input::NearestTile(x, NULL, true) && tileItr->rect.y == Input::NearestTile(NULL, y, true)) {
							list::DeleteNode<Tile>(roomItr->tileList, tileItr);
							goto FullBreak;
						}

						tileItr = (Tile*)tileItr->next;
					} while (tileItr != nullptr);

					roomItr = roomItr->next;
				} while (roomItr != nullptr);
			FullBreak:;
			targetMap->SaveMap();
			}
			
		}
		RenderWindow();
		
	}
	SDL_Quit();
	return 0;
}





