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