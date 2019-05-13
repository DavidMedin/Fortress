#include "../header/Keyboard.h"
#include <stdio.h>


int isDownOnce(const Uint8* state, SDL_Scancode current) {
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
int isDownOnceMouse(int* x,int* y,int state) {
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