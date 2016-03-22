//Enemy.h

/*
This file will contain all of the enemy classes in
Recoil. These will all be extensions of the class
Character which I will make, which will also be 
in this file allowing me to easily manipulate 
these enemies through functions, as functions will 
be able to accept all kinds of enemies due to 
polymorphism.
*/

#pragma once
#include "Recoil.h"

//base character for enemies and player
class Character {
public:
	//void setAnimation(int animationSet, int animationFrame);
	//void nextFrame();


	int health;			//health of a character
	bool usesGravity;	//whether an object is affected by gravity or not
	sf::Vector2f pos;	//position of the character
	sf::Sprite sprite;	//character sprite
};