#pragma once
#include "Character.h"

//Player.cpp

/*
This file contains the code for
the player class.
*/

using namespace std;

//weapon constructor
Weapon::Weapon(std::string weaponName, sf::Texture &weaponIcon, std::vector<std::vector<sf::Texture>> &frontAnimations, std::vector<std::vector<sf::Texture>> &backAnimations,
	bool isAutomatic, std::string projectileType, int projectiles, float projectileVelocity, bool projectileGravity, float accuracy, float fireRate, float recoil,
	float splashDamage, float splashRange) {
	
	this->weaponName = weaponName;
	this->weaponIcon.setTexture(weaponIcon);
	animationsBack = backAnimations;
	animationsFront = frontAnimations;

	this->isAutomatic = isAutomatic;
	this->projectileType = projectileType;
	this->projectiles = projectiles;
	this->projectileVelocity = projectileVelocity;
	this->projectileGravity = projectileGravity;
	this->accuracy = accuracy;
	this->fireRate = fireRate;
	this->recoil = recoil;

	this->splashDamage = splashDamage;
	this->splashRange = splashRange;
}

//empty function
void Weapon::fire() {

}

//NOTE: these weapon functions work because the front and back arm will always have matching length animations and the same amount of sets
bool Weapon::setAnimation(int newSet, int newFrame) {
	//if newSet is a valid index of animations
	if (newSet < animationsFront.size()) {
		//if newFrame is a valid index of the animation set
		if (newFrame < animationsFront[newSet].size()) {
			//set the animation
			currentAnimation = newSet;
			currentFrame = newFrame;

			//update the sprites
			spriteFront.setTexture(animationsFront[currentAnimation][currentFrame]);
			spriteBack.setTexture(animationsBack[currentAnimation][currentFrame]);

			//return true
			return true;
		}
		else {
			//if not a valid index, notify console
			cout << "Weapon Animator: newFrame index is out of range" << endl;
			//return false
			return false;
		}
	}
	else {
		//if not a valid animation set, notify console
		cout << "Weapon Animator: newFrame index is out of range" << endl;
		//return false
		return false;
	}
}

//cycles to the next frame in an animation when called
//will loop back to start if on last frame
void Weapon::nextFrame() {
	//if the animation set is comprised of more than one frame
	//if it is only one frame long, don't bother doing anything
	if (animationsFront[currentAnimation].size() > 1) {
		//increment current frame
		++currentFrame;

		//if index out of range
		if (currentFrame >= animationsFront[currentAnimation].size()) {
			//go back to start of the loop
			currentFrame = 0;
		}

		//update the sprites
		spriteFront.setTexture(animationsFront[currentAnimation][currentFrame]);
		spriteBack.setTexture(animationsBack[currentAnimation][currentFrame]);
	}
}

Player::Player(sf::Vector2f spawnPos, vector<vector<sf::Texture>> &animations, vector<Weapon> weapons, float health, int maxHealth, int score) {
	//set console character name
	charName = "Player";

	//set variables
	this->animations = animations;
	this->health = health;
	this->maxHealth = maxHealth;
	this->score = score;

	//player movement stats
	walkAccel = 3;
	walkSpeed = 5;
	jumpVelocity = 2;

	doesClip = true;
	usesGravity = true;

	//animation variables
	currentAnimation = 0;
	currentFrame = 0;

	//sprite creation
	sprite.setTexture(animations[currentAnimation][currentFrame]);
	//position the sprite
	sprite.setPosition(spawnPos);
}

Player::Player() {

}

void Player::control(int moveX, bool jump, float deltaTime) {
	//if the player is on the ground
	if (isGrounded) {
		//if the player is below the max walk speed
		if (velocity.x < walkSpeed) {
			//move the player horizontally according to moveX and deltaTime
			velocity.x += walkAccel * deltaTime * moveX;
		}

		//if the player jumped
		if (jump) {
			//set the vertical speed to the jump speed
			velocity.y = -jumpVelocity;
			//set isGrounded to false
			isGrounded = false;
		}
	}
}