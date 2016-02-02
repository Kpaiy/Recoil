//Textures.cpp

#include "Recoil.h"

 Terrain::Terrain() {

}

//load all terrain textures
bool Terrain::load() {
	//if something messed up, return false
	if (!TextureUtils::loadTexture("resources/graphics/dirt.png", dirt)) {
		return false;
	}
	
	return true;
}

Misc::Misc() {

}

bool Misc::load() {
	//return false if something goes wrong during loading of each texture
	if (!TextureUtils::loadTexture("resources/graphics/missingTexture.png", missing)) {
		return false;
	}

	return true;
}

Textures::Textures() {

}

//load each subtexture group
//if something goes wrong, return false
bool Textures::load() {
	//attempt to load terrain textures
	if (!terrain.load()) {
		//if something goes wrong, return false
		return false;
	}

	//attempt to load miscellaneous textures
	if (!misc.load()) {
		return false;
	}

	return true;
}