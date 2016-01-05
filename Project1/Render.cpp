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

	//update the display
	window.display();
}