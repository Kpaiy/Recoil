//Recoil.cpp

/*
This file contains the instructions to undergo when the file is
executed, and the bare minimum game loop,, calling functions 
from other files.
*/

#include "Recoil.h"

using namespace std;

//define the constructor
Recoil::Recoil() {
}

//define the execute manager
int Recoil::Execute() {
	//!INITIATION

	//shiny console shenanigans
	cout << "----------------------" << endl;
	cout << "        Recoil        " << endl;
	cout << "Created by Craig Smith" << endl;
	cout << "----------------------" << endl;
	
	//load stuff
	if (!Init()) {
		//if loading went wrong, give up now
		//notify through console
		cout << "Loading halted due to errors" << endl << endl;
		//pause the console
		system("pause");

		return -1;
	}

	//!PROGRAM LOOP
	while (running && window.isOpen()) {
		//iterate through user input given this frame
		sf::Event event;
		while (window.pollEvent(event)) {
			//chuck the event over to the event processing function
			Event(event);
		}
		//run game logic
		Logic();
		//update the game screen
		Render();
	}

	//!TERMINATION
	
	//run the cleanup function
	Close();
}

//this is run when the application is opened
int main(int argc, char* argv[]) {
	//construct the game
	Recoil recoil;
	return recoil.Execute();

	return 0;
}