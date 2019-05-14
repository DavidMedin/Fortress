#include "../header/Timer.h"

Timer::Timer() {
	temptime = SDL_GetTicks();
	time = SDL_GetTicks();
}
void Timer::UpdateTime() {
	time = (SDL_GetTicks() - temptime) + time;
	temptime = SDL_GetTicks();
}
void Timer::ResetTime() {
	time = 0;
}