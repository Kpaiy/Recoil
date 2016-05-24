//Render.cpp

/*
This function will take all of the active
game objects and GUI elements, and display
them on the screen.
*/

#include "Recoil.h"

using namespace std;

void Recoil::Render() {

	//clear the window
	window.clear(sf::Color::White);

	//draw game objects to window
	window.draw(missingSprite);

	//iterate through tiles container
	for (std::vector<Tile>::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		window.draw(it->sprite);
	}

	//draw all projectiles
	for (vector<Projectile>::iterator it = projectiles[0].begin(); it != projectiles[0].end(); ++it) {
		window.draw(it->sprite);
	}
	for (vector<Projectile>::iterator it = projectiles[1].begin(); it != projectiles[1].end(); ++it) {
		window.draw(it->sprite);
	}

	//draw the player
	player.draw(window);

	//update the display
	window.display();
}