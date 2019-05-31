#include "../header/physics.h"
using namespace physics;

void MainPhysics(){
	Actor* actorItr = targetMap->actorList;
	do {
		// records position

		// iterate through vector list and apply this one
		// compare origin vs now for new compressed vector
		actorItr = (Actor*)actorItr->next;
	} while (actorItr != nullptr);
}