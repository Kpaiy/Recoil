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
	sf::Vector2f pivotFront, sf::Vector2f pivotBack, bool isAutomatic, std::string projectileType, int projectiles, float projectileVelocity, bool projectileGravity, float accuracy, float fireRate, float recoil,
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

	//set up weapon sprites
	this->pivotBack = pivotBack;
	this->pivotFront = pivotFront;
	currentAnimation = 0;
	currentFrame = 0;
	spriteFront.setTexture(animationsFront[currentAnimation][currentFrame]);
	spriteBack.setTexture(animationsBack[currentAnimation][currentFrame]);
	spriteFront.setOrigin(pivotFront);
	spriteBack.setOrigin(pivotBack);
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

void Weapon::move(sf::Vector2f shoulder, sf::Vector2f aimPos) {
	//find the angle from the player to the aim position
	float rotation = atan2(aimPos.y - shoulder.y, aimPos.x - shoulder.x) * 180 / PI;

	cout << rotation << endl;

	//adjust the pivot point depending on whether the player is facing right or left
	if (abs(rotation) <= 90) {
		//if the player is looking left, use the default pivots
		spriteFront.setOrigin(pivotFront);
		spriteBack.setOrigin(pivotBack);
	}
	else {
		//if the player is looking left, invert the y pivot
		spriteFront.setOrigin(pivotFront.x, spriteFront.getLocalBounds().height - pivotFront.y);
		spriteBack.setOrigin(pivotBack.x, spriteBack.getLocalBounds().height - pivotBack.y);
	}

	//move the weapon sprites to the player position
	spriteFront.setPosition(shoulder);
	spriteBack.setPosition(shoulder);

	//set the weapon arms' rotation by the found angle
	spriteFront.setRotation(rotation);
	spriteBack.setRotation(rotation);
}

Player::Player(sf::Vector2f spawnPos, vector<vector<sf::Texture>> &animations, vector<Weapon> weapons, float health, int maxHealth, int score) {
	//set console character name
	charName = "Player";

	//set variables
	this->animations = animations;
	this->health = health;
	this->maxHealth = maxHealth;
	this->score = score;

	//shoulders
	shoulder = sf::Vector2f(15, 30);

	//player movement stats
	walkAccel = 2;
	walkSpeed = 1;
	jumpVelocity = 0.8;

	doesClip = true;
	usesGravity = true;

	//animation variables
	currentAnimation = 0;
	currentFrame = 0;

	//sprite creation
	sprite.setTexture(animations[currentAnimation][currentFrame]);
	//set the origin to the shoulder
	sprite.setOrigin(shoulder);
	//position the sprite
	sprite.setPosition(spawnPos);

	//get weapons
	this->weapons = weapons;
	//set the equipped weapon
	equippedWeapon = 0;
}

Player::Player() {

}

//performs all required frame by frame functions
void Player::update(float gravity, float deltaTime, std::vector<Tile> &terrainTiles, sf::Vector2f aimPos) {
	//move the player
	move(gravity, deltaTime, terrainTiles);
	//move and aim the currently equipped weapon
	weapons[equippedWeapon].move(sprite.getPosition(), aimPos);
}

void Player::draw(sf::RenderWindow &window) {
	//draw the back arm of the currently equipped weapon
	window.draw(weapons[equippedWeapon].spriteBack);
	//draw the player
	window.draw(sprite);
	//draw the front arm of the currently equipped weapon
	window.draw(weapons[equippedWeapon].spriteFront);
}

void Player::control(int moveX, bool jump, float deltaTime) {
	//if the player is on the ground
	if (isGrounded) {
		//if the player is not attempting to exceed the maximum walk speed
		if (!(moveX * velocity.x > walkSpeed) && moveX != 0) {
			//move the player horizontally according to moveX and deltaTime
			velocity.x += walkAccel * deltaTime * moveX * friction;
		}
		else {
			velocity.x -= velocity.x * friction * deltaTime;
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