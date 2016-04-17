#pragma once

#include <iostream>
#include <cmath>

//SFML libraries
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

//own code
#include "Terrain.h"

#define PI 3.14159265358975323846264338327950

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

//projectile template
class Projectile {
public:
	float projectileVelocity;	//velocity of the projectile
	bool projectileGravity;		//whether the projectile experiences gravity
	float damage;				//damage inflicted per projectile
	float recoil;				//velocity on player from each shot of weapon
	float splashDamage;			//splash damage, if applicable
	float splashRange;			//splash range, if applicable

	bool hurtsPlayer;			//whether the projectile can harm the player

	sf::Sprite sprite;			//sprite for the projectile
};

//base character for enemies and player
class Character {
public:
	//sets the animation for the character
	bool setAnimation(int newSet, int newFrame = 0);
	//cycles between frames
	void nextFrame();

	//moves the sprite depending on their velocity, and factors in gravity
	void move(float gravity, float deltaTime, std::vector<Tile> &terrainTiles);

	//list of animations, which are lists of textures
	std::vector<std::vector<sf::Texture>> animations;
	//current animation set index
	int currentAnimation;
	int currentFrame;

	//character sprite
	sf::Sprite sprite;

	//character name
	std::string charName;

	float health;			//health of a character
	int maxHealth;			//max health of a character

	bool doesClip;			//whether the character can pass through terrain
	bool isGrounded;		//whether the player is standing on the ground

	bool usesGravity;		//whether an object is affected by gravity or not
	sf::Vector2f velocity;	//current velocity of the character
};

class Weapon {
public:
	//weapon constructor
	Weapon(std::string weaponName, sf::Texture &weaponIcon, std::vector<std::vector<sf::Texture>> &frontAnimations, std::vector<std::vector<sf::Texture>> &backAnimations,
		bool isAutomatic, std::string projectileType, int projectiles, float projectileVelocity, bool projectileGravity, float accuracy, float fireRate, float recoil,
		float splashDamage = 0, float splashRange = 0);
	//fire weapon
	void fire();

	//weapon name
	std::string weaponName;

	//sets the animation for the weapons
	bool setAnimation(int newSet, int newFrame = 0);
	//cycles between frames
	void nextFrame();

	//sprite for front arm
	sf::Sprite spriteFront;
	//sprite for back arm
	sf::Sprite spriteBack;

	//weapon GUI icon
	sf::Sprite weaponIcon;

	//list of animations for front arm
	std::vector<std::vector<sf::Texture>> animationsFront;
	//list of animations for back arm
	std::vector<std::vector<sf::Texture>> animationsBack;
	//current animation set index
	int currentAnimation;
	int currentFrame;

	//weapon stats
	bool isAutomatic;			//whether the player can hold down the button to fire or has to click repeatedly
	std::string projectileType; //type of projectile to spawn
	int projectiles;			//amount of projectiles fired per shot
	float projectileVelocity;	//velocity of the projectile
	bool projectileGravity;		//whether the projectile experiences gravity
	float accuracy;				//angle of deviation from aim point
	float fireRate;				//minimum time between each shot, in seconds
	float damage;				//damage inflicted per projectile
	float recoil;				//velocity on player from each shot of weapon
	float splashDamage;			//splash damage, if applicable
	float splashRange;			//splash range, if applicable

	//if the player has the weapon
	bool hasWeapon;
};

class Player : public Character {
public:
	//empty constructor
	Player();
	//player constructor
	Player(sf::Vector2f spawnPos, std::vector<std::vector<sf::Texture>> &animations, std::vector<Weapon> weapons, float health = 100, int maxHealth = 100, int score = 0);

	//applies player input
	void control(int moveX, bool jump, float deltaTime);

	int score;						//player score

	float walkAccel;				//player acceleration when walking on the ground
	float walkSpeed;				//max speed the player can reach while walking
	float jumpVelocity;				//velocity generated when the player jumps

	//weapons
	std::vector<Weapon> weapons;	//list of weapons
	int equippedWeapon;				//index of the weapon the player is currently using
};