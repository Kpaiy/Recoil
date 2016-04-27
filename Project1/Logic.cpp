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

	//check for particular held keys
	int moveX = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		moveX -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		moveX += 1;
	}

	//process player control
	player.control(moveX, jump, deltaTime);

	//move the player
	player.move(GRAVITY, deltaTime, tiles);

	//update the camera
	updateCamera(deltaTime);

	//reset input trackers
	jump = false;

}

//incomplete function
void Recoil::updateCamera(float deltaTime) {
	camCounter += deltaTime;
	
	//if not exceeding max dampen cycles per second
	if (camCounter >= 1 / dampRate) {
		//find the distance between the camera and the center of the player
		sf::Vector2f distance = player.center() - camPos;

		//move the camPos
		camPos.x += distance.x * camDamp;
		camPos.y += distance.y * camDamp;

		//reset counter
		camCounter = 0;
	}

	//reset offset
	offset.x = 0;
	offset.y = 0;

	//iterate through all shake commands
	for (vector<sf::Vector2f>::iterator it = shakes.begin(); it != shakes.end();) {
		//offset camera by a random value from -magnitude to magnitude
		offset.x += rand() % (int)(2 * it->y + 1) - it->y;
		offset.y += rand() % (int)(2 * it->y + 1) - it->y;

		//subtract deltaTime from duration
		it->x -= deltaTime;

		//if duration is less than or equal to zero
		if (it->x <= 0) {
			//delete the element
			it = shakes.erase(it);
		}
		else {
			//otherwise, check the next element
			++it;
		}
	}
	
	//move the camera to the new camPos + offset
	camera.setCenter(camPos + offset);

	//update the camera status to the window
	window.setView(camera);
}

void Recoil::screenShake(float duration, int magnitude) {
	//append shake command to list of shakes
	sf::Vector2f shake;
	//set duration and magnitude
	shake.x = duration;
	shake.y = magnitude;

	//append to list of shakes
	shakes.push_back(shake);
}