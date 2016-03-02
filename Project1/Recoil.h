//Recoil.h

/*
This file will be the main file, managing and organising
all of my source code in an easy to understand manner.
This file contains a Recoil class, which will handle all
elements of the game.
*/

#pragma once

//importing of libraries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//SFML libraries
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

//own code
#include "Utilities.h"
#include "Textures.h"
#include "Terrain.h"

class Recoil {
private:
	//whether the game is running or not
	bool running;

	//game window
	sf::RenderWindow window;

	//camera
	sf::View camera;

	//current menu or game state
	//0 - Main Menu, 1 - Game, 2 - Settings
	int menuState;

	//whether the player is currently in a game
	bool playing;

	//textures
	Textures textures;

	//level chunks management
	
	//chunk containers
	std::vector<std::vector<std::vector<char>>> chunk1;			//Chunk containers are classed based their position on the
	std::vector<std::vector<std::vector<char>>> chunk2;			//numpad after the keyword "chunk".
	std::vector<std::vector<std::vector<char>>> chunk3;			//
	std::vector<std::vector<std::vector<char>>> chunk4;			//  789			i.e chunk7 contains tiles designed to fit
	std::vector<std::vector<std::vector<char>>> chunk5;			//  456			in the top left of a level.
	std::vector<std::vector<std::vector<char>>> chunk6;			//  123
	std::vector<std::vector<std::vector<char>>> chunk7;
	std::vector<std::vector<std::vector<char>>> chunk8;
	std::vector<std::vector<std::vector<char>>> chunk9;

	bool loadAllChunks(std::string filename, int chunkWidth);
	void loadChunk(std::vector<std::vector<std::vector<char>>> &chunkContainer, std::ifstream &file, std::string &tempString);
	

	//level generation functions
	bool generateTiles(std::vector<std::vector<char>> map);
	std::vector<std::vector<char>> generateLevel();

public:
	//!RECOIL
	//the constructor function, allowing everything to work
	Recoil();

	//when the application is run. Handles all other functions, like Init.
	int Execute();
	//initiation of game, returns false when weird stuff happens.
	bool Init();
	//handles player input
	void Event(sf::Event event);
	//logic executed each frame
	void Logic();
	//draw game elements to the window
	void Render();
	//run this when user quits game
	void Close();

	//!SETTINGS
	int RES_WIDTH;		//resolution horizontally
	int RES_HEIGHT;		//resolution vertically
	bool FULLSCREEN;
	int TILE_SIZE;		//size of each tile unit in pixels
	int CHUNK_WIDTH;	//size of each terrain chunk in tiles

	sf::Sprite missingSprite;

	//container for all terrain tile pointers
	std::vector<Tile> tiles;
};
