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

	if (!TextureUtils::loadTexture("resources/graphics/backdrop.png", backDrop)) {
		return false;
	}
	//have the backdrop tileable
	backDrop.setRepeated(true);
	//make the tile texture tileable
	dirt.setRepeated(true);
	
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

Protag::Protag() {

}

bool Protag::load() {
	//return false if something goes wrong during loading of each texture
	if (!TextureUtils::loadTexture("resources/graphics/tempPlayer.png", idle)) {
		return false;
	}
	if (!TextureUtils::loadTexture("resources/graphics/frontWeapon.png", fGun)) {
		return false;
	}
	if (!TextureUtils::loadTexture("resources/graphics/backWeapon.png", bGun)) {
		return false;
	}

	return true;
}

Projectiles::Projectiles() {

}

bool Projectiles::load() {
	if (!TextureUtils::loadTexture("resources/graphics/bullet.png", pistol)) {
		return false;
	}

	return true;
}

Enemies::Enemies() {

}

bool Enemies::load() {
	if (!TextureUtils::loadTexture("resources/graphics/wraith.png", wraith)) {
		return false;
	}

	return true;
}

Textures::Textures() {

}

UI::UI() {
	uiColor.r = 0;
	uiColor.g = 0;
	uiColor.b = 0;
	uiColor.a = 120;

	healthBar.r = 255;
	healthBar.g = 0;
	healthBar.b = 0;
	healthBar.a = 255;

	uiBar.x = 330;
	uiBar.y = 10;

	barContainer.x = 405;
	barContainer.y = 40;

	containerY = 50;
	barOffset = 60;
	iconOffset = 25;
	outlineWidth = 3;
}

bool UI::load() {
	if (!TextureUtils::loadTexture("resources/graphics/heart.png", heart)) {
		return false;
	}

	if (!TextureUtils::loadTexture("resources/graphics/warning.png", warning)) {
		return false;
	}

	//return true
	return true;
}

//load each subtexture group
//if something goes wrong, return false
bool Textures::load() {
	//attempt to load miscellaneous textures
	if (!misc.load()) {
		return false;
	}

	//attempt to load terrain textures 
	if (!terrain.load()) {
		//if something goes wrong, return false
		return false;
	}

	if (!projectiles.load()) {
		return false;
	}

	if (!enemies.load()) {
		return false;
	}

	//load player textures
	if (!player.load()) {
		return false;
	}

	if (!ui.load()) {
		return false;
	}


	return true;
}