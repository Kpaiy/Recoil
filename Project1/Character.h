#pragma once

#include <iostream>
#include <cmath>
#include <vector>

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
	//projectile constructor
	Projectile(sf::Vector2f shoulder, int offset, float angle, float speed, float damage, sf::Texture* bulletTex, std::vector<std::vector<Projectile>> &projectiles, float accuracy, bool playerOwned, float splashDamage = 0, float splashRange = 0, bool gravity = false);

	//move function
	void move(float deltaTime, float gravity);

	//projectile sprite
	sf::Sprite sprite;
	sf::Texture* bulletTex;

	//weapon stats
	sf::Vector2f velocity;				//velocity of the projectile
	bool usesGravity;						//whether the projectile experiences gravity
	float damage;						//damage inflicted per projectile
	float splashDamage;					//splash damage, if applicable
	float splashRange;					//splash range, if applicable

	bool hurtsPlayer;			//whether the projectile can harm the player
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

	//finds the center of the character
	sf::Vector2f center();

	//list of animations, which are lists of textures
	std::vector<std::vector<sf::Texture>> animations;
	//current animation set index
	int currentAnimation;
	int currentFrame;

	//friction value of tile the character is on
	float friction;

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
	Weapon(std::string weaponName, sf::Texture &weaponIcon, sf::Texture* bulletTex, std::vector<std::vector<sf::Texture>> &frontAnimations, std::vector<std::vector<sf::Texture>> &backAnimations,
		sf::Vector2f pivotFront = sf::Vector2f(8, 8), sf::Vector2f pivotBack = sf::Vector2f(5,5), bool isAutomatic = true, int projectiles = 1, float damage = 5,
		float projectileVelocity = 1500, bool projectileGravity = false, float accuracy = 0.05, float fireRate = 0.05, float recoil = 2, float splashDamage = 0, float splashRange = 0);
	//fire weapon
	void fire(sf::Vector2f aimPos, std::vector<std::vector<Projectile>> &projectiles);
	//updates the weapon
	void update(sf::Vector2f aimPos, sf::Vector2f shoulder, float deltaTime);

	//weapon name
	std::string weaponName;

	//sets the animation for the weapons
	bool setAnimation(int newSet, int newFrame = 0);
	//cycles between frames
	void nextFrame();

	//moves and aims the weapons
	void move(sf::Vector2f shoulder, sf::Vector2f aimPos);

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

	//pivot point of the arms
	sf::Vector2f pivotFront;
	sf::Vector2f pivotBack;

	//weapon stats
	bool isAutomatic;			//whether the player can hold down the button to fire or has to click repeatedly
	sf::Texture* bulletTex;		//texture for the bullet
	int projectiles;			//amount of projectiles fired per shot
	float projectileVelocity;	//velocity of the projectile
	bool projectileGravity;		//whether the projectile experiences gravity
	float accuracy;				//angle of deviation from aim point
	float fireRate;				//minimum time between each shot, in seconds
	float shotTimer;			//time since the last shot
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

	void update(float gravity, float deltaTime, std::vector<Tile> &terrainTiles, sf::Vector2f aimPos);
	void draw(sf::RenderWindow &window);
	void fire(sf::Vector2f aimPos, std::vector<std::vector<Projectile>> &projectiles);

	//applies player input
	void control(int moveX, bool jump, float deltaTime);

	int score;						//player score

	float walkAccel;				//player acceleration when walking on the ground
	float walkSpeed;				//max speed the player can reach while walking
	float jumpVelocity;				//velocity generated when the player jumps

	sf::Vector2f shoulder;		//location on the player where the weapon arms will pivot around

	//weapons
	std::vector<Weapon> weapons;	//list of weapons
	int equippedWeapon;				//index of the weapon the player is currently using
};