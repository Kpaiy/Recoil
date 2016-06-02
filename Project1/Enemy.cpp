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
			sprite.setTexture(*animations[currentAnimation][currentFrame]);
			
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
		sprite.setTexture(*animations[currentAnimation][currentFrame]);
	}
}

//moves the sprite, factoring in gravity if applicable
void Character::move(float deltaTime, float gravity, vector<Tile> &terrainTiles, vector<sf::Vector2f> &shakes, float PROJECTILE_RANGE, int RES_WIDTH, int RES_HEIGHT) {
	//remember old velocity
	sf::Vector2f oldVel;
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

			//if the projectile is near the character
			sf::Vector2f distance = sprite.getPosition() - it->sprite.getPosition();
			if (abs(distance.x) < PROJECTILE_RANGE * RES_WIDTH && abs(distance.y) < PROJECTILE_RANGE * RES_HEIGHT) {
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
					//calculate impact damage
					impactDamage(abs(velocity.x), shakes);
					//set the x velocity to zero
					velocity.x = 0;

				}
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

			//if the projectile is near the character
			sf::Vector2f distance = sprite.getPosition() - it->sprite.getPosition();
			if (abs(distance.x) < PROJECTILE_RANGE * RES_WIDTH && abs(distance.y) < PROJECTILE_RANGE * RES_HEIGHT) {
				//if the character collides with the tile
				if (charRect.intersects(tileRect)) {
					//if y velocity is positive
					if (velocity.y >= 0) {
						//find the distance from the bottom edge of character and top edge of tile
						float overlap = tileRect.top - (charRect.top + charRect.height);
						//move the player by the found distance
						sprite.move(0, overlap);
						//save the friction value of the tile
						friction = it->friction;
						//set isGrounded to true
						isGrounded = true;
					}
					else {
						//otherwise, find the distance between the bottom edge of tile and top edge of character
						float overlap = tileRect.top + tileRect.height - charRect.top;
						//move the player by the found distance
						sprite.move(0, overlap);
					}
					//calculate impact damage
					impactDamage(abs(velocity.y), shakes);
					//set the y velocity to zero
					velocity.y = 0;

				}
			}
		}
	}

	//if the y velocity is not equal to zero
	if (velocity.y != 0) {
		//set isGrounded to false
		isGrounded = false;
	}

}

void Character::impactDamage(float velocity, vector<sf::Vector2f> &shakes) {
	float minV = 7.5; //minimum velocity required to incur fall damage

	//if the velocity is enough to cause impact damage
	if (velocity >= minV) {
		float result = 3.5 * pow(velocity - minV, 0.75) + 5;
		//damage the player by the found result
		damage(result, shakes);
	}
}

bool Character::damage(float damage, vector<sf::Vector2f> &shakes) {
	health -= damage;
	if (health <= 0) {
		health = 0;
		return true;
	}
	else {
		return false;
	}
}

//returns center of the character
sf::Vector2f Character::center() {
	//get bounding box
	sf::FloatRect bounds = sprite.getGlobalBounds();

	//find center of bounding box
	sf::Vector2f center;
	center.x = bounds.left + bounds.width / 2;
	center.y = bounds.top + bounds.height / 2;

	return center;
}

//enemy constructor
Enemy::Enemy(sf::Vector2f spawnPos, std::vector<Enemy> &enemies, std::vector<std::vector<sf::Texture*>> animations, sf::Texture* bulletTex, float thinkTime, float fireRate, float damage, float accuracy, float projectileSpeed, int health, bool usesGravity, bool doesClip) {
	//set the enemy's health
	maxHealth = health;
	this->health = health;

	this->usesGravity = usesGravity;
	this->doesClip = doesClip;

	//animator setup
	this->animations = animations;
	currentAnimation = 0;
	currentFrame = 0;

	//AI setup
	thinkCounter = 0;
	thinkSpeed = thinkTime;

	//enemy stats
	speed = 65;
	minDistance = 100;

	//projectile stats
	this->fireRate = fireRate;
	fireCounter = 0;
	
	projectileDamage = damage;
	this->accuracy = accuracy;
	this->projectileSpeed = projectileSpeed;

	this->bulletTex = bulletTex;
	
	//sprite setup
	sprite.setTexture(*animations[currentAnimation][currentFrame]);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);		//set the origin to the center of the sprite
	sprite.setPosition(spawnPos);

	//score value
	scoreValue = 100;

	//append enemy to list of enemies
	enemies.push_back(*this);
}

void Enemy::choice() {
	//randomly determine whether the enemy will shoot and move
	shooting = !!(rand() % 2);
	moving = !!(rand() % 2);
	
	//set the enemy think counter to its think time
	thinkCounter = thinkSpeed;
}

void Enemy::control(float deltaTime, sf::Vector2f playerPos, vector<vector<Projectile>> &projectiles) {
	//find the angle of the player from the enemy, in radians
	float playerAngle = atan2(playerPos.y - sprite.getPosition().y, playerPos.x - sprite.getPosition().x);

	//if the enemy does not collide with terrain and is not affected by gravity
	if (!(doesClip && usesGravity)) {
		//if the enemy is moving
		if (moving) {
			//set the velocity to be towards the player
			velocity.x = cosf(playerAngle) * speed;
			velocity.y = sinf(playerAngle) * speed;

			//if the enemy is advancing too close
			if (sqrt(pow(playerPos.x - sprite.getPosition().x, 2) + pow(playerPos.y - sprite.getPosition().y, 2)) <= minDistance) {
				//stop moving
				moving = false;
			}
		}
	}

	//if the enemy is shooting and the weapon is able to be fired
	if (shooting && fireCounter <= 0) {
		//find playerAngle in degrees
		playerAngle *= 180 / PI;
		//add a random value from -accuracy to accuracy to the angle
		playerAngle += (-accuracy + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * accuracy))));

		//create the projectile
		Projectile(sprite.getPosition(), 0, playerAngle, projectileSpeed, projectileDamage, bulletTex, projectiles, false);

		//activate the weapon cooldown
		fireCounter = fireRate;
	}
}

bool Enemy::update(float deltaTime, sf::Vector2f playerPos, vector<vector<Projectile>>& projectiles, float gravity, vector<Tile> &tiles, vector<sf::Vector2f> &shakes, float PROJECTILE_RANGE, int RES_WIDTH, int RES_HEIGHT) {
	//subtract deltaTime from thought counter if it is positive
	if (thinkCounter > 0) {
		thinkCounter -= deltaTime;
	}
	//subtract deltaTime from weapon counter if it is positive
	if (fireCounter > 0) {
		fireCounter -= deltaTime;
	}

	//if the enemy is able to think again
	if (thinkCounter <= 0) {
		//run choice function
		choice();
		//activate thought cooldown
		thinkCounter = thinkSpeed;
	}

	//control the enemy
	control(deltaTime, playerPos, projectiles);
	//move the enemy
	move(deltaTime, gravity, tiles, shakes, PROJECTILE_RANGE, RES_WIDTH, RES_HEIGHT);

	//if the enemy is dead
	if (health <= 0) {
		//return false
		return false;
	}
	else {
		//otherwise, return true
		return true;
	}
}