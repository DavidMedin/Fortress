#include "../header/main.h"





int NearestTile(int x, int y, bool round) {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	int xPos = (int)(((float)x + floor((float)offX * scale - (w / 2))) / scale);
	int yPos = (int)(((float)y + floor((float)offY * scale - (h / 2))) / scale);
	int xRound = (int)floor((float)xPos / (float)BASE_SIZE) * BASE_SIZE;
	int yRound = (int)floor((float)yPos / (float)BASE_SIZE) * BASE_SIZE;
	if (round == true) {
		return x != NULL ? xRound : yRound;
	}
	else {
		return x != NULL ? xPos : yPos;
	}
}




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
	
	string input;

	Timer* moveTime = new Timer();
	int speed = 2;


	const Uint8* state = SDL_GetKeyboardState(NULL);
	SDL_Event event; 
	while (1) {
		//game loop!!!
		while (SDL_PollEvent(&event)){
			SDL_Scancode keyPressed = event.key.keysym.scancode;
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
			if (keyPressed == SDL_SCANCODE_P) {
				isEdit = !isEdit;
				printf("Edit mode is %s!\n", isEdit ? "On" : "Off");
			}
			if (keyPressed == SDL_SCANCODE_RETURN) {
				isTypeing = !isTypeing;
				if (!isTypeing) {
					SDL_StopTextInput();
					input.insert(0, "Data/");
					input += ".png";
					SDL_Texture* tex = ImgLoad(input.c_str());
					if (!(tex == nullptr)) {
						editTexPath = input;
						list::AddNode<Texture>(mapLoadTexes);
						mapLoadTexes->tex = tex;
						mapLoadTexes->texName = new Obj();
						mapLoadTexes->texName->texName = input;
						
						printf("\n");
					}
					else printf("that texture doesn't exist!\n");
					input.clear();
				}
				else SDL_StartTextInput();
				printf("Typing mode is %s!\n", isTypeing ? "On" : "Off");
			}
			if (isTypeing && keyPressed == SDL_SCANCODE_BACKSPACE) {
				input.pop_back();
				printf("\b \b");
			}
		}

		if (event.type == SDL_TEXTINPUT && isTypeing == true) {
			if (event.key.repeat == 0) {
				printf("%s", event.text.text);
				input.append(event.text.text);
			}
		}
	}
		if(moveTime->time >= speed && !isTypeing) {

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
		}
		
				
			
		
		moveTime->UpdateTime();
		
		if (isEdit) {
			int x, y;
			if (Input::isDownOnceMouse(&x, &y,SDL_BUTTON_LEFT) == 1) {
				hub->AddTile(NearestTile(x,NULL,true), NearestTile(NULL,y,true), 0, editTexPath.c_str());
				targetMap->SaveMap();
			}
			else if (Input::isDownOnceMouse(&x, &y, SDL_BUTTON_RIGHT) == 1) {
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





