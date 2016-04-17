//Terrain.cpp

#include "Terrain.h"

//Tile constructor
Tile::Tile(sf::Texture& tileTexture, sf::Vector2f position, std::vector<Tile>& tilePointers, float friction) {
	//assign friction value
	this->friction = friction;
	
	//set up sprite
	//assign tile texture
	sprite.setTexture(tileTexture);
	//position tile
	sprite.setPosition(position);
	//add pointer to self to a list of tile pointers
	tilePointers.push_back(*this);
}

Tile::Tile() {

}