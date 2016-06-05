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

	FRAME_CAP = 75;

	GRAVITY = 4.2;

	CONSIDER_RANGE = 1.2;
	PROJECTILE_RANGE = 0.4;

	//set a seed for random generation
	srand(time(0));

	//load settings
	FileUtils::loadSettings(string("settings.cfg"), RES_WIDTH, RES_HEIGHT, FULLSCREEN);
	cout << "----------------------" << endl;

	//assign variable values here and load assets
	
	//load textures
	textures.load();

	//load font
	font.loadFromFile("resources/graphics/cour.ttf");

	//load chunks
	loadAllChunks("chunks.rcl", CHUNK_WIDTH);

	//button container setup
	vector<Button> tempButtons;
	buttons.push_back(tempButtons);
	buttons.push_back(tempButtons);
	buttons.push_back(tempButtons);
	buttons.push_back(tempButtons);

	//button setup
	Button(sf::IntRect(RES_WIDTH - 350, 50, 350, 70), sf::Color(200, 200, 200), sf::Color(100, 100, 100), "New Game", 1, font, 32, buttons, 0);

	//load sprites
	
	//level setup
	//int chunkHorizontal = 4;		//count of horizontal chunks in the level to be generated
	//int chunkVertical = 3;			//count of vertical chunks
	//generateLevel(sf::Vector2i(chunkHorizontal, chunkVertical), 12);

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
	camDamp = 0.1;
	camera.setSize(RES_WIDTH, RES_HEIGHT);
	camera.setCenter(camPos);
	window.setView(camera);	
	window.setFramerateLimit(FRAME_CAP);
	window.setVerticalSyncEnabled(true);	//enable v-sync to prevent screen tearing
	offset = sf::Vector2f(0,0);
	dampRate = 75;
	camCounter = 0;

	hud.setSize(RES_WIDTH, RES_HEIGHT);
	hud.setCenter(RES_WIDTH / 2, RES_HEIGHT / 2);
	

	menuState = 0;
	playing = false;

	//disable os repeating keystrokes when a key is held down
	window.setKeyRepeatEnabled(false);

	//if no hiccups from the first bit, return true
	return true;
}