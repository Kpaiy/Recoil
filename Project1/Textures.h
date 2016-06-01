//Textures.h

/*
A class structure which will hold all textures
in a neat fashion, easily callable.
*/

#include "Utilities.h"

class Terrain {
public:
	Terrain();
	bool load();

	sf::Texture dirt;
};

class Misc {
public:
	Misc();
	bool load();

	sf::Texture missing;
};

class Protag {
public:
	Protag();
	bool load();

	sf::Texture idle;
	sf::Texture fGun;
	sf::Texture bGun;
};

class Projectiles {
public:
	Projectiles();
	bool load();

	sf::Texture pistol;
};

class Enemies {
public:
	Enemies();
	bool load();

	sf::Texture wraith;
};

class UI {
public:
	UI();
	bool load();

	sf::Color uiColor;
	sf::Color healthBar;
	
	sf::Vector2f uiBar;
	sf::Vector2f barContainer;
	int containerY;
	int barOffset;
	int outlineWidth;

	sf::Texture heart;
};

class Textures {
public:
	Textures();
	bool load();

	Terrain terrain;
	Misc misc;
	Protag player;
	Projectiles projectiles;
	Enemies enemies;
	UI ui;
};