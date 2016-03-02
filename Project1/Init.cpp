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
	TILE_SIZE = 100;
	CHUNK_WIDTH = 25;

	//load settings
	FileUtils::loadSettings(string("settings.cfg"), RES_WIDTH, RES_HEIGHT, FULLSCREEN);
	cout << "----------------------" << endl;

	//assign variable values here and load assets
	
	//load textures
	textures.load();

	//load sprites
	missingSprite.setTexture(textures.misc.missing);

	//shabby code to generate a two dimensional container for tile generation
	//just for testing, will have a function to generate levels later (duh)
	char map0[5] = { 'd','d','d','d','d' };
	char map1[5] = { 'd',' ',' ',' ','d' };
	vector<char> vmap0;
	vector<char> vmap1;
	vmap0.assign(map0, map0 + 5);
	vmap1.assign(map1, map1 + 5);
	vector<vector<char>> map;
	map.push_back(vmap0);
	map.push_back(vmap1);
	map.push_back(vmap1);
	map.push_back(vmap1);
	map.push_back(vmap0);
	
	//generateTiles(map);
	generateTiles(generateLevel());

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