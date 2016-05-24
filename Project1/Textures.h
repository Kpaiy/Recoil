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

class Textures {
public:
	Textures();
	bool load();

	Terrain terrain;
	Misc misc;
	Protag player;
	Projectiles projectiles;
};