#pragma once
#include "Character.h"

//Enemy.cpp

/*
This file contains all code for enemies
and characters, as well as the base
character class.
*/

using namespace std;

//this function just provides a nicer way to switch between animations without directly modifying variables
//this reduces the places in code in which I can make errors, as I will not modify the wrong variable using this subroutine
bool Character::setAnimation(int newSet, int newFrame) {
	//if newSet is a valid index of animations
	if (newSet < animations.size()) {
		//if newFrame is a valid index of the animation set
		if (newFrame < animations[newSet].size()) {
			//set the animation
			currentAnimation = newSet;
			currentFrame = newFrame;

			//update the sprite
			sprite.setTexture(animations[currentAnimation][currentFrame]);

			//return true
			return true;
		}
		else {
			//if not a valid index, notify console
			cout << charName << ": Animator: newFrame index is out of range" << endl;
			//return false
			return false;
		}
	}
	else {
		//if not a valid animation set, notify console
		cout << charName << ": Animator: newFrame index is out of range" << endl;
		//return false
		return false;
	}
}

//cycles to the next frame in an animation when called
//will loop back to start if on last frame
void Character::nextFrame() {
	//if the animation set is comprised of more than one frame
	//if it is only one frame long, don't bother doing anything
	if (animations[currentAnimation].size() > 1) {
		//increment current frame
		++currentFrame;

		//if index out of range
		if (currentFrame >= animations[currentAnimation].size()) {
			//go back to start of the loop
			currentFrame = 0;
		}

		//update the sprite
		sprite.setTexture(animations[currentAnimation][currentFrame]);
	}
}

//moves the sprite, factoring in gravity if applicable
void Character::move(float deltaTime, float gravity, vector<Tile> &terrainTiles) {
	//if the character uses gravity
	if(usesGravity) {
		//accelerate the character using acceleration strength and how long they've been accelerated
		velocity.y += gravity * deltaTime;
	}

	//move the sprite by the x velocity
	sprite.move(velocity.x * deltaTime, 0);
	//if the character cannot clip through terrain
	if(doesClip) {
		//iterate through terrain tiles
		for (vector<Tile>::iterator it = terrainTiles.begin(); it != terrainTiles.end(); ++it) {
			sf::FloatRect charRect = sprite.getGlobalBounds();
			sf::FloatRect tileRect = it->sprite.getGlobalBounds();
			//if the character collides with the tile
			if (charRect.intersects(tileRect)) {
				//if x velocity is positive
				if (velocity.x >= 0) {
					//find the distance from the right edge of character and left edge of tile
					float overlap = tileRect.left - (charRect.left + charRect.width);
					//move the player by the found distance
					sprite.move(overlap, 0);
				}
				else {
					//otherwise, find the distance between the right edge of tile and left edge of character
					float overlap = tileRect.left + tileRect.width - charRect.left;
					//move the player by the found distance
					sprite.move(overlap, 0);
				}
				//set the x velocity to zero
				velocity.x = 0;

			}
		}
	}

	//move sprite by y velocity
	sprite.move(0, velocity.y * deltaTime);
	//if the character cannot clip through terrain
	if (doesClip) {
		//iterate through terrain tiles
		for (vector<Tile>::iterator it = terrainTiles.begin(); it != terrainTiles.end(); ++it) {
			sf::FloatRect charRect = sprite.getGlobalBounds();
			sf::FloatRect tileRect = it->sprite.getGlobalBounds();
			//if the character collides with the tile
			if (charRect.intersects(tileRect)) {
				//if y velocity is positive
				if (velocity.y >= 0) {
					//find the distance from the bottom edge of character and top edge of tile
					float overlap = tileRect.top - (charRect.top + charRect.height);
					//move the player by the found distance
					sprite.move(0, overlap);
				}
				else {
					//otherwise, find the distance between the bottom edge of tile and top edge of character
					float overlap = tileRect.top + tileRect.height - charRect.top;
					//move the player by the found distance
					sprite.move(0, overlap);
				}
				//set the y velocity to zero
				velocity.y = 0;

			}
		}
	}
}