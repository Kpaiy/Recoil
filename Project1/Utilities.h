//Utilities.h

/*
This file contains all of the utility
functions I create.
*/

#pragma once

#include <iostream>
#include <string>

#include<SFML\Graphics.hpp>

class TextureUtils {
public:
	static bool loadTexture(std::string src, sf::Texture* texture);
	static bool loadTextureToSprite(std::string src, sf::Texture* texture, sf::Sprite* sprite);
};
