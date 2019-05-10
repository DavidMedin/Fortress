#pragma once
#include <SDL_timer.h>
class Timer {
public:
	 int time;
	 int temptime;
	 void UpdateTime();
	 void ResetTime();
	 Timer();
};