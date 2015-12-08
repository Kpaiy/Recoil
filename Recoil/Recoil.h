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
#include <string>

//SFML libraries
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

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

public:
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


};