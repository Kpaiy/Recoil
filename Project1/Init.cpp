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
	DEBUG = false;

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
	if (!textures.load()) {
		//if an error occured, halt loading
		return false;
	}

	//load font
	if (!font.loadFromFile("resources/graphics/cour.ttf")) {
		//if failed, halt loading
		return false;
	}

	//load chunks
	if (!loadAllChunks("chunks.rcl", CHUNK_WIDTH)) {
		//if an error occured, return false
		return false;
	}

	//button container setup
	vector<Button> tempButtons;
	buttons.push_back(tempButtons);
	buttons.push_back(tempButtons);
	buttons.push_back(tempButtons);
	buttons.push_back(tempButtons);

	//button setup
	Button(sf::IntRect(RES_WIDTH - 350, 250, 350, 50), sf::Color(200, 200, 200), sf::Color(100, 100, 100), "New Game", 1, font, 32, buttons, 0);				//0,0
	Button(sf::IntRect(0, 250, 350, 50), sf::Color(200, 200, 200), sf::Color(100, 100, 100), "Resume Game", -1, font, 32, buttons, 3);							//3,0
	Button(sf::IntRect(RES_WIDTH - 350, 310, 350, 50), sf::Color(200, 200, 200), sf::Color(100, 100, 100), "Options", 1, font, 32, buttons, 0);					//0,1
	Button(sf::IntRect(RES_WIDTH - 350, 370, 350, 50), sf::Color(200, 200, 200), sf::Color(100, 100, 100), "Quit", 1, font, 32, buttons, 0);					//0,2

	Button(sf::IntRect(0, 50, 800, 100), sf::Color(200, 200, 200), sf::Color(200, 200, 200), "Settings", -1, font, 72, buttons, 2);								//2,0
	Button(sf::IntRect(50, 180, 500, 70), sf::Color(200, 200, 200), sf::Color(200, 200,200), "Resolution", -1, font, 56, buttons, 2);							//2,1
	Button(sf::IntRect(RES_WIDTH - 350, RES_HEIGHT - 50, 350, 50), sf::Color(200, 200, 200), sf::Color(100, 100, 100), "Back", 1, font, 32, buttons, 2);		//2,2
	Button(sf::IntRect(100 , 315, 300, 40), sf::Color(200, 200, 200), sf::Color(100, 100, 100), "Toggle Fullscreen", 0, font, 28, buttons, 2);					//2,3
	Button(sf::IntRect(100, 260, 300, 40), sf::Color(200, 200, 200), sf::Color(100, 100, 100), "Native Resolution", 0, font, 28, buttons, 2);					//2,4
	Button(sf::IntRect(425, 260, 300, 40), sf::Color(200, 200, 200), sf::Color(100, 100, 100), "1600 x 900", 0, font, 28, buttons, 2);							//2,5
	Button(sf::IntRect(750, 260, 300, 40), sf::Color(200, 200, 200), sf::Color(100, 100, 100), "1280 x 720", 0, font, 28, buttons, 2);							//2,6


	//console shenanigans
	cout << "Opening window..." << endl;

	//if the fullscreen option is true
	if (FULLSCREEN) {
		//create a fullscreen window
		window.create(sf::VideoMode(RES_WIDTH, RES_HEIGHT), "Recoil", sf::Style::Fullscreen);
	}
	else {
		//otherwise, create a windowed window
		window.create(sf::VideoMode(RES_WIDTH, RES_HEIGHT), "Recoil", sf::Style::Close);
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
	

	menuState = -1;
	playing = false;

	//disable os repeating keystrokes when a key is held down
	window.setKeyRepeatEnabled(false);

	//if no hiccups from the first bit, return true
	return true;
}