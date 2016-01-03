//Init.cpp

/*
This file contains the code for loading all assets
for use in the game. If something goes wrong, this
function will return false, ceasing running of the
game.
*/

#include "Recoil.h"

using namespace std;

bool Recoil::Init() {
	//assign variable values here and load assets

	//console shenanigans
	cout << "Opening window..." << endl;

	//create window
	window.create(sf::VideoMode(1280, 720), "Recoil");

	menuState = 0;
	playing = false;

	//if no hiccups from the first bit, return true
	return true;
}