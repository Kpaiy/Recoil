//Utilities.h

/*
This file contains all of the utility
functions I create.
*/

#pragma once

#include "Recoil.h"

//!TEXTURE FUNCTIONS
class TextureUtils {
public:
	static bool loadTexture(std::string src, sf::Texture& texture);
	static bool loadTextureToSprite(std::string src, sf::Texture& texture, sf::Sprite& sprite);
};

//!FILE FUNCTIONS
class FileUtils {
public:
	static bool loadSettings(std::string filename, int& res_width, int& res_height, bool& fullscreen);
	static bool saveSettings(std::string filename, int& res_width, int& res_height, bool& fullscreen);

	static float stringToFloat(std::string string);
};