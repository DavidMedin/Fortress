#include "../header/Input.h"

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

int Input::isDownOnce(const Uint8* state, SDL_Scancode current) {
	static bool lastState = false;
	//printf("%d\n", lastState);
	if (state[current] && lastState == false) {
		lastState = true;
		return 1;
	}
	else if (!state[current] && lastState == true) {
		lastState = false;
		return 2;
	}
	return 0;
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
