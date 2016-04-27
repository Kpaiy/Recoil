//Terrain.h

/*
This file will contain all code relevant
to game terrain blocks and level generation.
*/

#pragma once

#include <SFML\Graphics.hpp>

//terrain will be block-based, using this class for each tile
class Tile {
public:
	Tile();
	Tile(sf::Texture& tileTexture, sf::Vector2f position, std::vector<Tile>& tilePointers, float friction = 3);

	//tile graphic
	sf::Sprite sprite;

	//friction player experiences moving on tile
	float friction;

};