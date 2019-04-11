#pragma once
#include <SDL_timer.h>
class Timer {
public:
	 int time;
	 int temptime;
	 void TimeInit();
	 void UpdateTime();
	 void ResetTime();
};