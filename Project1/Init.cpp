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
	//declare constants
	TILE_SIZE = 50;
	CHUNK_WIDTH = 25;

	//set a seed for random generation
	srand(time(0));

	//load settings
	FileUtils::loadSettings(string("settings.cfg"), RES_WIDTH, RES_HEIGHT, FULLSCREEN);
	cout << "----------------------" << endl;

	//assign variable values here and load assets
	
	//load textures
	textures.load();

	//load chunks
	loadAllChunks("chunks.rcl", CHUNK_WIDTH);

	//load sprites
	missingSprite.setTexture(textures.misc.missing);
	
	//generateTiles(map);
	generateTiles(generateLevel(sf::Vector2i(3,3)));

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

	//set up the game camera
	//NOTE: the size and centre of the camera have been drastically increased in order to see the random level generation
	camera.setSize(RES_WIDTH, RES_HEIGHT);
	camera.setCenter(0.5 * RES_WIDTH, 0.5 * RES_HEIGHT);
	window.setView(camera);	

	menuState = 0;
	playing = false;

	//if no hiccups from the first bit, return true
	return true;
}