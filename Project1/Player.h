#pragma once
#include "Enemy.h" //has Character base class

//Player.h

/*
This file contains all player relevant 
classes. The player class will extend 
off the basic Character class, in 
Enemy.h.
*/

/*
class Weapon {
public:
	//weapon constructor
	Weapon(std::string weaponName, sf::Texture &weaponIcon, std::vector<std::vector<sf::Texture>> &frontAnimations, std::vector<std::vector<sf::Texture>> &backAnimations,
		bool isAutomatic, std::string projectileType, int projectiles, float projectileVelocity, bool projectileGravity, float accuracy, float fireRate, float recoil,
		float splashDamage = -1, float splashRange = -1);
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
	//player constructor
	Player(sf::Vector2f spawnPos, std::vector<std::vector<sf::Texture>> animations, float health = 100, int maxHealth = 100, int score = 0);

	int score;						//player score

	//weapons
	std::vector<Weapon> weapons;	//list of weapons
	int equippedWeapon;				//index of the weapon the player is currently using
};

*/