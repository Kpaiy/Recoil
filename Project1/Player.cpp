#pragma once
#include "Character.h"

//Player.cpp

/*
This file contains the code for
the player class.
*/

using namespace std;

//projectile constructor
Projectile::Projectile(sf::Vector2f shoulder, int offset, float angle, float speed, float damage, sf::Texture* bulletTex, std::vector<std::vector<Projectile>> &projectiles, bool playerOwned, float splashDamage, float splashRange, bool gravity) {
	//calculate a new angle factoring in innacuracy
	
	//find the angle as a unit vector
	velocity.y = sinf(angle * PI / 180);
	velocity.x = cosf(angle * PI / 180);
	//multiply the velocity by the speed
	velocity.y *= speed;
	velocity.x *= speed;

	this->damage = damage;
	this->splashDamage = splashDamage;
	this->splashRange = splashRange;
	hurtsPlayer = !playerOwned;
	usesGravity = gravity;

	//sprite setup
	sprite.setTexture(*bulletTex);
	sprite.setOrigin(0, sprite.getLocalBounds().height / 2);
	//move the sprite away from the shoulder according to angle and offset
	sprite.setPosition(shoulder);
	sprite.move(cosf(angle * PI / 180) * offset, sinf(angle * PI / 180) * offset);
	sprite.setRotation(angle);

	//add the projectile to a list of projectiles
	projectiles[playerOwned].push_back(*this);
}

void Projectile::move(float deltaTime, float gravity) {
	//if the projectile experiences gravity
	if (usesGravity) {
		//accelerate particle downwards according to gravity and deltaTime
		velocity.y += gravity * deltaTime;
	}

	//move the projectile by its velocity multiplied by the delta time
	sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
}

bool Projectile::collide(Character character) {
	//if the projectile is colliding with the character
	if (sprite.getGlobalBounds().intersects(character.sprite.getGlobalBounds())) {
		//damage the character
		character.damage(damage);
		//return true
		return true;
	} else {
		//otherwise, return false
		return false;
	}
}

bool Projectile::collide(Tile tile) {
	//if the projectile is colliding with the terrain tile
	if (sprite.getGlobalBounds().intersects(tile.sprite.getGlobalBounds())) {
		//return true
		return true;
	} else {
		//otherwise return false
		return false;
	}
}

//weapon constructor
Weapon::Weapon(std::string weaponName, sf::Texture &weaponIcon, sf::Texture* bulletTex, std::vector<std::vector<sf::Texture*>> &frontAnimations, std::vector<std::vector<sf::Texture*>> &backAnimations,
	sf::Vector2f pivotFront, sf::Vector2f pivotBack, bool isAutomatic, int projectiles, float damage, float projectileVelocity, bool projectileGravity, float accuracy, float fireRate, float recoil,
	float splashDamage, float splashRange) {
	
	this->weaponName = weaponName;
	this->weaponIcon.setTexture(weaponIcon);
	animationsBack = backAnimations;
	animationsFront = frontAnimations;

	this->isAutomatic = isAutomatic;
	this->bulletTex = bulletTex;
	this->projectiles = projectiles;
	this->damage = damage;
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
	spriteFront.setTexture(*animationsFront[currentAnimation][currentFrame]);
	spriteBack.setTexture(*animationsBack[currentAnimation][currentFrame]);
	spriteFront.setOrigin(pivotFront);
	spriteBack.setOrigin(pivotBack);
}

//empty function
sf::Vector2f Weapon::fire(sf::Vector2f aimPos, std::vector<std::vector<Projectile>> &projectiles) {
	//recoil variable
	sf::Vector2f recoil;
	recoil.x = 0;
	recoil.y = 0;

	//if the weapon cooldown has expired
	if (shotTimer <= 0) {
		//for each projectile this shot
		for (int i = 0; i < this->projectiles; i++) {
			//calculate accuracy deviation
			float activeAngle = spriteFront.getRotation() + (-accuracy + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * accuracy))));
			//create the projectile
			Projectile(spriteFront.getPosition(), spriteFront.getLocalBounds().width, activeAngle, projectileVelocity, damage, bulletTex, projectiles, accuracy, true);
			//calculate recoil to the player
			recoil.x -= cosf(activeAngle * PI / 180) * this->recoil;
			recoil.y -= sinf(activeAngle * PI / 180) * this->recoil;
		}

		//activate the weapon cooldown
		shotTimer = fireRate;
	}

	//return the recoil
	return recoil;
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
			spriteFront.setTexture(*animationsFront[currentAnimation][currentFrame]);
			spriteBack.setTexture(*animationsBack[currentAnimation][currentFrame]);

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
		spriteFront.setTexture(*animationsFront[currentAnimation][currentFrame]);
		spriteBack.setTexture(*animationsBack[currentAnimation][currentFrame]);
	}
}

void Weapon::move(sf::Vector2f shoulder, sf::Vector2f aimPos) {
	//find the angle from the player to the aim position
	float rotation = atan2(aimPos.y - shoulder.y, aimPos.x - shoulder.x) * 180 / PI;

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

void Weapon::update(sf::Vector2f aimPos, sf::Vector2f shoulder, float deltaTime) {
	//decrement the shot cooldown by the deltaTime if it is greater than zero
	if (shotTimer > 0) {
		shotTimer -= deltaTime;
	}

	//move the weapon arms
	move(shoulder, aimPos);
}

Player::Player(sf::Vector2f spawnPos, vector<vector<sf::Texture*>> &animations, vector<Weapon> weapons, float health, int maxHealth, int score) {
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
	sprite.setTexture(*animations[currentAnimation][currentFrame]);
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
	//update the currently equipped weapon
	weapons[equippedWeapon].update(aimPos, sprite.getPosition(), deltaTime);
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

//when the player fires a weapon
void Player::fire(sf::Vector2f aimPos, std::vector<std::vector<Projectile>> &projectiles) {
	//call the fire function for the equipped weapon
	sf::Vector2f recoil = weapons[equippedWeapon].fire(aimPos, projectiles);

	//apply recoil
	velocity.x += recoil.x;
	velocity.y += recoil.y;
}