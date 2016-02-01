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

	sf::Texture dirtTile;
};

class Misc {
public:
	Misc();
	bool load();

	sf::Texture missing;
};


class Textures {
public:
	Textures();
	bool load();

	Terrain terrain;
	Misc misc;
};