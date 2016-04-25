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

	GRAVITY = 2;

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
	//temporary things
	missingSprite.setTexture(textures.misc.missing);
	vector<sf::Texture> tempVec;
	tempVec.push_back(textures.player.idle);
	tempAnimations.push_back(tempVec);
	vector<Weapon> tempWeaps;

	//temporary player constructor
	player = Player(sf::Vector2f((float)500, (float)500), tempAnimations, tempWeaps);
	
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
	camPos = player.center();
	camDamp = 0.1;
	camera.setSize(RES_WIDTH, RES_HEIGHT);
	camera.setCenter(camPos);
	window.setView(camera);	
	offset = sf::Vector2f(0,0);


	menuState = 0;
	playing = false;

	//disable os repeating keystrokes when a key is held down
	window.setKeyRepeatEnabled(false);

	//if no hiccups from the first bit, return true
	return true;
}