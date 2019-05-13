#include "../header/main.h"
#include <string>
//void RenderWindow();
//SDL_Texture* ImgLoad(char* path);

void RenderWindow();
SDL_Texture* ImgLoad(const char* path);
int NearestTile(int x, int y, bool round);

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	window = SDL_CreateWindow("Fortress", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, INIT_WIDTH, INIT_HEIGHT, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_GetCurrentDisplayMode(0, &DM);
	
	loadedTextures = nullptr;
	mapLoadTexes = nullptr;
	hub = new Map("Data/map.map");
	targetMap = hub;
	targetRoom = targetMap->roomList;
	/*room* roomList = nullptr;
	room* tmpRoom = list::AddNode<room>(roomList);
	Tile* tmpTile = list::AddNode<Tile>(tmpRoom->tileList);
	Tile* boi = new Tile;
	boi->texName = "boi";
	boi->isWalkable = true;
	*tmpTile = *boi;
	*/

	Timer* moveTime = new Timer();
	int speed = 2;

	const Uint8* state = SDL_GetKeyboardState(NULL);
	SDL_Event event; 

	while (1) {
		//game loop!!!
		SDL_PollEvent(&event);
		if (moveTime->time >= speed) {
			bool did = false;
			if (state[SDL_SCANCODE_A]) {
				offX -= 1;
				moveTime->ResetTime();
			}
			if (state[SDL_SCANCODE_D]) {
				offX += 1;
				moveTime->ResetTime();
			}
			if (state[SDL_SCANCODE_W]) {
				offY -= 1;
				moveTime->ResetTime();
			}
			if (state[SDL_SCANCODE_S]) {
				offY += 1;
				moveTime->ResetTime();
			}
			if (state[SDL_SCANCODE_Q]) {
				scale += .01f;
				moveTime->ResetTime();
			}
			if (state[SDL_SCANCODE_E]) {
				scale -= .01f;
				moveTime->ResetTime();
			}
			if (isDownOnce(state,SDL_SCANCODE_P) == 1) {
				isEdit = !isEdit;
				printf("Edit mode is %s!\n", isEdit ? "On" : "Off");
			}
		/*	if (did) {
				moveTime->ResetTime();
			}*/
			//did = false;
		}
		moveTime->UpdateTime();
		/*if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			printf("boi");
		}*/
		if (isEdit) {
			int x, y;
			if (isDownOnceMouse(&x, &y,SDL_BUTTON_LEFT) == 1) {
				hub->AddTile(NearestTile(x,NULL,true), NearestTile(NULL,y,true), 0, "Data/Grass.png");
				targetMap->SaveMap();
			}
			else if (isDownOnceMouse(&x, &y, SDL_BUTTON_RIGHT) == 1) {
				Room* roomItr = hub->roomList;
				do {
					Tile* tileItr = roomItr->tileList;
					do {
						if (tileItr->rect.x == NearestTile(x, NULL, true) && tileItr->rect.y == NearestTile(NULL, y, true)) {
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
int NearestTile(int x,int y,bool round) {
	int xPos = (int)(((float)x + floor((float)offX * scale)) / scale);
	int yPos = (int)(((float)y + floor((float)offY * scale)) / scale);
	int xRound = (int)floor((float)xPos / ((float)BASE_SIZE)) * (int)((float)BASE_SIZE);
	int yRound = (int)floor((float)yPos / (float)BASE_SIZE) * (int)(float)BASE_SIZE;
	if (round == true) {
		return x != NULL ? xRound : yRound;
	}
	else {
		return x != NULL ? xPos : yPos;
	}
}


void RenderWindow() {	
	// fetching and adding the unique textures and putting them into the correct texture lsit
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
	
		Tile* tileItr = targetRoom->tileList;
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
			SDL_GetWindowSize(window, &w, &h);
			tmpRect = tileItr->rect;




			static bool lazy = false;
			if (lazy == false) {
				int targetLength = targetRoom->width > targetRoom->height ? targetRoom->width : targetRoom->height;
				scale = float((targetRoom->width == targetLength ? w : h)) / float(targetLength);
				lazy = true;
			}
			
			// screen width / w
			//tmpRect.w *= WIDTH / roomItr->width;
			//tmpRect.h *= HEIGHT / roomItr->height;
			
			tmpRect.w = (int)ceil(float(tileItr->rect.w) * scale);
			tmpRect.h = (int)ceil(float(tileItr->rect.h) * scale);
			tmpRect.x = (int)floor(float(tileItr->rect.x - offX) * scale);
			tmpRect.y = (int)floor(float(tileItr->rect.y - offY) * scale);
			
			// next make a relative coord system and move the camera
			// then add scaling of camera
			// test multiple rooms
			if (tmpTex == nullptr) {
				printf("tmpTex is null");
			}
			SDL_RenderCopy(renderer, tmpTex, NULL, &tmpRect);
			tileItr = (Tile*)tileItr->next;
		} while (tileItr != nullptr);
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
