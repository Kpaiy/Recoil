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
	//load settings
	FileUtils::loadSettings(string("settings.cfg"), &RES_WIDTH, &RES_HEIGHT, &FULLSCREEN);

	//assign variable values here and load assets
	
	//attempt load missingTexture texture to sprite
	if (!TextureUtils::loadTextureToSprite("resources/graphics/missingTexture.png", &missingTexture, &missingSprite)) {
		//if unable to load, return false
		return false;
	}

	//console shenanigans
	cout << "Opening window..." << endl;

	//if the fullscreen option is true
	if (FULLSCREEN) {
		//create a fullscreen window
		window.create(sf::VideoMode(RES_WIDTH, RES_HEIGHT), "Recoil", sf::Style::Fullscreen);
	}
	else {
		//otherwise, create a windowed window
		window.create(sf::VideoMode(RES_WIDTH, RES_HEIGHT), "Recoil");
	}
	

	menuState = 0;
	playing = false;

	//if no hiccups from the first bit, return true
	return true;
}