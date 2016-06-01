#pragma once

//Recoil.h

/*
This file will be the main file, managing and organising
all of my source code in an easy to understand manner.
This file contains a Recoil class, which will handle all
elements of the game.
*/

//importing of libraries
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

//SFML libraries
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics\Color.hpp>

//own code
#include "Utilities.h"
#include "Textures.h"
#include "Terrain.h"
#include "Character.h"

#define PI 3.14159265358975323846264338327950

class Recoil {
private:
	//whether the game is running or not
	bool running;

	//game window
	sf::RenderWindow window;

	//camera
	sf::View camera;
	sf::View hud;			//hud view
	sf::Vector2f camPos;
	float camDamp;			//dampening factor of the camera
	int dampRate;			//max amount of times to dampen per second
	float camCounter;
	sf::Vector2f offset;	//offset caused by screenshake
	std::vector<sf::Vector2f> shakes;		//screenshakes, each element being a container for duration and magnitude

	//current menu or game state
	//0 - Main Menu, 1 - Game, 2 - Settings
	int menuState;

	//whether the player is currently in a game
	bool playing;

	//player control tracker
	bool jump;
	bool fire;

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
	std::vector<std::vector<char>> generateLevel(sf::Vector2i dimensions);
	std::vector<std::vector<char>> randChunk(std::vector<std::vector<std::vector<char>>> chunk);

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

	//tracks the player
	void updateCamera(float deltaTime);
	void screenShake(float time, int magnitude);
	 
	//!SETTINGS
	int RES_WIDTH;		//resolution horizontally
	int RES_HEIGHT;		//resolution vertically
	bool FULLSCREEN;
	int TILE_SIZE;		//size of each tile unit in pixels
	int CHUNK_WIDTH;	//size of each terrain chunk in tiles

	//GAME CONSTANTS
	float GRAVITY;		//acceleration due to gravity

	//CLOCK AND TIME
	sf::Clock clock;
	float deltaTime;

	//temporary things
	sf::Sprite missingSprite;
	//std::vector<std::vector<sf::Texture>> tempAnimations;

	//container for all terrain tile pointers
	std::vector<Tile> tiles;

	//projectile container, two segments, one for player-owned, one for enemy-owned, respectively
	std::vector<std::vector<Projectile>> projectiles;
	//enemy container
	std::vector<Enemy> enemies;

	//player
	Player player;
};
