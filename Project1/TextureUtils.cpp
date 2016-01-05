//TextureUtils.cpp

/*
This file contains custom functions to aid
with textures and sprites.
*/

#include "Utilities.h"

using namespace std;

//A function to load a texture into the program. Will return false if something goes wrong.
//First argument is location of texture, second argument is texture variable to load into.
bool TextureUtils::loadTexture(std::string src, sf::Texture* texture) {
	//attempt to load texture
	if ((*texture).loadFromFile(src)) {
		//if succesful, notify via console and return true
		cout << "Loaded texture: " << src << endl;
		return true;
	}
	else {
		//if not succesful, return false and notify
		cout << "Unable to load texture: " << src << endl;
		return false;
	}
}

//Loads texture and plonks it onto a sprite all in one. Returns just like above function.
//Arg 1: Location of texture; Arg 2: texture to load into; Arg 3: Sprite to load texture into
bool TextureUtils::loadTextureToSprite(std::string src, sf::Texture* texture, sf::Sprite* sprite) {
	//attempt to load texture
	if (loadTexture(src, texture)) {
		//if succesful, attach to sprite and return true
		(*sprite).setTexture(*texture);
		return true;
	}
	else {
		//otherwise, return false
		return false;
	}
}