//Event.cpp

/*
This function will manage input from the user, and turn it into usable variables
for the logic functions, enabling user input to be efficiently processed and
utilised.
*/

#include "Recoil.h"

using namespace std;

void Recoil::Event(sf::Event event) {
	//detect different types of events
	switch(event.type) {
	
	//if the user closed the window
	case sf::Event::Closed:
		//set running to false
		running = false;
		break;

	//if the user pressed a key
	case sf::Event::KeyPressed:
		//multiway selection depending on the key pressed
		switch (event.key.code) {
		default:
			break;
		}

	//if not one of the above, do nothing
	default:
		break;
	}
}