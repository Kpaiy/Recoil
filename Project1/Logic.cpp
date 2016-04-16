//Logic.cpp

/*
This function will manage all of the game's
processes, running each frame. 
*/

#include "Recoil.h"

using namespace std;

void Recoil::Logic() {
	//get the time since the last frame, used to calculate velocity changes
	//taken as seconds so multiplication is simple
	deltaTime = clock.restart().asSeconds();

	//move the player
	player.move(GRAVITY, deltaTime, tiles);
}