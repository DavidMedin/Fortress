#include "../header/Input.h"

int Input::isDownOnce(const Uint8* state, SDL_Scancode current) {
	static bool lastState = false;
	if (state[current] && lastState == false) {
		lastState = true;
		return 1;
	}
	
	else if (state[current] == 0 && lastState == true) {
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
