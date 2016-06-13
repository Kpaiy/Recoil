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

	//current camera pos, including offset
	sf::Vector2f currentCamPos = camPos + offset;

	//iterate through tiles container
	for (std::vector<Tile>::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		//tile distance from camera center
		sf::Vector2f distance = it->sprite.getPosition() - currentCamPos;
		//if the tile is close to the camera
		if (abs(distance.x) < CONSIDER_RANGE * RES_WIDTH && abs(distance.y) < CONSIDER_RANGE * RES_HEIGHT) {
			//draw the sprite
			window.draw(it->sprite);
		}
	}

	//draw non solid tiles
	for (vector<Tile>::iterator it = decor.begin(); it != decor.end(); ++it) {
		//distance from camera center
		sf::Vector2f distance = it->sprite.getPosition() - currentCamPos;
		//if close to the camera
		if (abs(distance.x) < CONSIDER_RANGE * RES_WIDTH && abs(distance.y) < CONSIDER_RANGE * RES_HEIGHT) {
			//draw the sprite
			window.draw(it->sprite);
		}
	}

	//draw projectiles
	for (vector<Projectile>::iterator it = projectiles[0].begin(); it != projectiles[0].end(); ++it) {
		//distance from camera center
		sf::Vector2f distance = it->sprite.getPosition() - currentCamPos;
		//if the close to the camera
		if (abs(distance.x) < CONSIDER_RANGE * RES_WIDTH && abs(distance.y) < CONSIDER_RANGE * RES_HEIGHT) {
			//draw the sprite
			window.draw(it->sprite);
		}
	}
	for (vector<Projectile>::iterator it = projectiles[1].begin(); it != projectiles[1].end(); ++it) {
		//distance from camera center
		sf::Vector2f distance = it->sprite.getPosition() - currentCamPos;
		//if the close to the camera
		if (abs(distance.x) < CONSIDER_RANGE * RES_WIDTH && abs(distance.y) < CONSIDER_RANGE * RES_HEIGHT) {
			//draw the sprite
			window.draw(it->sprite);
		}
	}

	//draw enemies
	for (vector<Enemy>::iterator it = enemies.begin(); it != enemies.end(); ++it) {
		//distance from camera center
		sf::Vector2f distance = it->sprite.getPosition() - currentCamPos;
		//if the close to the camera
		if (abs(distance.x) < CONSIDER_RANGE * RES_WIDTH && abs(distance.y) < CONSIDER_RANGE * RES_HEIGHT) {
			//draw the sprite
			window.draw(it->sprite);
		}
	}

	//draw the player if they are alive
	if (player.health > 0) {
		player.draw(window);
	}

	//switch to the HUD view to draw hud elements
	window.setView(hud);

	//if the player is alive
	if (player.health > 0) {
		//health container element
		sf::RectangleShape container(textures.ui.barContainer);
		container.setFillColor(textures.ui.uiColor);
		container.setPosition(0, textures.ui.containerY);
		window.draw(container);

		//health bar
		sf::RectangleShape healthBar(textures.ui.uiBar);
		healthBar.setFillColor(sf::Color::Transparent);
		healthBar.setOutlineColor(sf::Color(0, 0, 0, textures.ui.healthBar.a));
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

		//draw the score
		int textOffset = 10;
		container.setPosition(RES_WIDTH - container.getLocalBounds().width, textures.ui.containerY);
		window.draw(container);
		sf::Text scoreText;
		scoreText.setString(to_string(player.score));
		scoreText.setFont(font);
		scoreText.setColor(sf::Color::White);
		scoreText.setStyle(sf::Text::Bold);
		scoreText.setCharacterSize(34);
		scoreText.setOrigin(scoreText.getLocalBounds().width, scoreText.getLocalBounds().height);
		scoreText.setPosition(RES_WIDTH - textOffset, textures.ui.containerY + container.getLocalBounds().height / 2);
		window.draw(scoreText);
	}
	else {
		//draw a semi-transparent white over the game scene
		sf::RectangleShape fade;
		fade.setFillColor(sf::Color(255, 255, 255, 100));
		fade.setPosition(0, 0);
		fade.setSize(sf::Vector2f(RES_WIDTH, RES_HEIGHT));
		window.draw(fade);
		//write game over to the screen
		sf::Text gameOver;
		gameOver.setString("Game Over");
		gameOver.setFont(font);
		gameOver.setColor(sf::Color::Black);
		gameOver.setCharacterSize(56);
		gameOver.setOrigin(gameOver.getLocalBounds().width / 2, gameOver.getLocalBounds().height);
		gameOver.setPosition(RES_WIDTH / 2, RES_HEIGHT / 2 - 100);
		window.draw(gameOver);
		//write their final score to the screen
		sf::Text scoreText;
		scoreText.setString("Your score: " + to_string(player.score));
		scoreText.setFont(font);
		scoreText.setColor(sf::Color::Black);
		scoreText.setStyle(sf::Text::Bold);
		scoreText.setCharacterSize(56);
		scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height);
		scoreText.setPosition(RES_WIDTH / 2 , RES_HEIGHT / 2);

		window.draw(scoreText);
	}

	//if debug is true
	if (DEBUG) {
		//draw the framerate to the bottom left of the screen
		sf::Text debugStats;
		debugStats.setString("Framerate: " + to_string((int)(1 / deltaTime)));
		debugStats.setFont(font);
		debugStats.setColor(sf::Color::White);
		debugStats.setCharacterSize(32);
		debugStats.setOrigin(0, debugStats.getLocalBounds().height);
		debugStats.setPosition(0, RES_HEIGHT - 50);
		window.draw(debugStats);
		//write the amount of projectiles
		debugStats.setString("Projectile count: " + to_string((int)(projectiles[0].size() + projectiles[1].size())));
		debugStats.move(0, -debugStats.getLocalBounds().height);
		window.draw(debugStats);
		//write the amount of enemies
		debugStats.setString("Enemy count: " + to_string((int)(enemies.size())));
		debugStats.move(0, -debugStats.getLocalBounds().height);
		window.draw(debugStats);
	}

	//switch back to the camera
	window.setView(camera);

	//update the display
	window.display();
}