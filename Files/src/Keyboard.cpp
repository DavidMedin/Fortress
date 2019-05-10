#include "../header/Keyboard.h"
#include <stdio.h>
static bool lastState = false;

int isDownOnce(const Uint8* state, SDL_Scancode current) {
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