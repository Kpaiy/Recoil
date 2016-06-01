//Render.cpp

/*
This function will take all of the active
game objects and GUI elements, and display
them on the screen.
*/

#include "Recoil.h"

using namespace std;

void Recoil::Render() {

	//clear the window
	window.clear(sf::Color::White);

	//draw the backdrop
	window.draw(backDrop);
	
	//draw game objects to window
	window.draw(missingSprite);

	//iterate through tiles container
	for (std::vector<Tile>::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		window.draw(it->sprite);
	}

	//draw all projectiles
	for (vector<Projectile>::iterator it = projectiles[0].begin(); it != projectiles[0].end(); ++it) {
		window.draw(it->sprite);
	}
	for (vector<Projectile>::iterator it = projectiles[1].begin(); it != projectiles[1].end(); ++it) {
		window.draw(it->sprite);
	}

	//draw all enemies
	for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		window.draw(it->sprite);
	}

	//draw the player
	player.draw(window);

	//switch to the HUD view to draw hud elements
	window.setView(hud);

	//health container element
	sf::RectangleShape container(textures.ui.barContainer);
	container.setFillColor(textures.ui.uiColor);
	container.setPosition(0, textures.ui.containerY);
	window.draw(container);

	//health bar
	sf::RectangleShape healthBar(textures.ui.uiBar);
	healthBar.setFillColor(sf::Color::Transparent);
	healthBar.setOutlineColor(sf::Color::Black);
	healthBar.setOutlineThickness(textures.ui.outlineWidth);
	healthBar.setPosition(textures.ui.barOffset, textures.ui.containerY + (textures.ui.barContainer.y - textures.ui.uiBar.y) / 2);
	window.draw(healthBar);
	healthBar.setFillColor(textures.ui.healthBar);
	healthBar.setOutlineThickness(0);
	healthBar.scale(player.health / player.maxHealth, 1);
	window.draw(healthBar);

	//heart icon
	sf::Sprite heartIcon;
	heartIcon.setTexture(textures.ui.heart);
	heartIcon.setOrigin(heartIcon.getLocalBounds().width / 2, heartIcon.getLocalBounds().height / 2);
	heartIcon.setPosition(textures.ui.iconOffset, textures.ui.containerY + textures.ui.barContainer.y / 2);
	window.draw(heartIcon);

	//switch back to the camera
	window.setView(camera);

	//update the display
	window.display();
}