//Terrain.cpp

#include "Terrain.h"

//Tile constructor
Tile::Tile(sf::Texture& tileTexture, sf::Vector2f position) {
	//set up sprite
	//assign tile texture
	sprite.setTexture(tileTexture);
	//position tile
	sprite.setPosition(position);
}

Tile::Tile() {

}