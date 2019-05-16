#include "../header/Input.h"

static SDL_Event event;
int speed = 2;
string input;
Timer* moveTime = new Timer();
const Uint8* state = SDL_GetKeyboardState(NULL);

void Input::CheckInput() {
	while (SDL_PollEvent(&event)) {
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
						list::AddNode<Obj>(texLoadQueue);
						texLoadQueue = new Obj();
						texLoadQueue->texName = input;

						printf("\n");
					}
					else printf("that texture doesn't exist!\n");
					input.clear();
					SDL_DestroyTexture(tex);
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
	if (moveTime->time >= speed && !isTypeing) {
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
}



int Input::isDownOnceMouse(int* x,int* y,int state) {
	static bool lastClick = false;
	if (SDL_GetMouseState(x,y) == SDL_BUTTON(state) && lastClick == false) {
		lastClick = true;
		return 1;
	}
	else if (!SDL_GetMouseState(x,y) == SDL_BUTTON(state) && lastClick == true) {
		lastClick = false;
		return 2;
	}
	return 0;
}

int Input::NearestTile(int x, int y, bool round) {
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