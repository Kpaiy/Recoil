//Menu.cpp

/*
This file contains all functions related to the
game's menus.
*/

#include "Recoil.h"

using namespace std;

//button constructor
Button::Button(sf::IntRect rect, sf::Color buttonColor, sf::Color highlightColor, std::string buttonText, int textAlign, sf::Font &font, int size, std::vector<std::vector<Button>> &buttons, int buttonIndex) {
	//offset used to position text
	int textOffset = 10;
	
	//create the rectangle shape from the rect argument
	buttonBox.setPosition(rect.left, rect.top);
	buttonBox.setSize(sf::Vector2f(rect.width, rect.height));

	//set the rectangle's color
	this->buttonColor = buttonColor;
	this->highlightColor = highlightColor;
	buttonBox.setFillColor(this->buttonColor);

	//create the text graphic
	text.setColor(sf::Color::Black);
	text.setFont(font);
	text.setString(buttonText);
	text.setCharacterSize(size);

	//set origin of text
	sf::FloatRect textDimensions = text.getLocalBounds();
	sf::FloatRect boxBounds = buttonBox.getGlobalBounds();
	//if align left
	if (textAlign == -1) {
		//set the origin to the middle left
		text.setOrigin(0, textDimensions.height);
		//position text
		text.setPosition(boxBounds.left + textOffset, boxBounds.top + boxBounds.height / 2);
	}
	//if aligbn center
	else if (textAlign == 0) {
		//set the origin to the center of the text
		text.setOrigin(textDimensions.width / 2, textDimensions.height);
		//position text
		text.setPosition(boxBounds.left + boxBounds.width / 2, boxBounds.top + boxBounds.height / 2);
	}
	//otherwise, align right
	else {
		//set the origin to the middle right
		text.setOrigin(textDimensions.width, textDimensions.height);
		//position text
		text.setPosition(boxBounds.left + boxBounds.width - textOffset, boxBounds.top + boxBounds.height / 2);
	}

	//append button to a list of buttons sorted by menu
	buttons[buttonIndex].push_back(*this);
}

//determines whether a point is contained within the button
bool Button::contains(sf::Vector2f mousePos) {
	return buttonBox.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void Button::update(sf::Vector2f mousePos) {
	//if the mouse is over the button
	if (contains(mousePos)) {
		//change to use the button's highlight colors
		buttonBox.setFillColor(highlightColor);
	}
	else {
		//otherwise, use the normal colors
		buttonBox.setFillColor(buttonColor);
	}
}

//draws a button to the screen
void Button::draw(sf::RenderWindow &window) {
	//draw the button box first
	window.draw(buttonBox);
	//draw the button text over the box
	window.draw(text);
}

void Recoil::menuEvent(sf::Event event) {
	//flag to check if settings were altered
	bool altered = false;
	//track old resolution values in case they are altered
	int oldResX = RES_WIDTH;
	int oldResY = RES_HEIGHT;
	//behave differently depending on the type of event
	switch (event.type) {
	//if the player closed the window
	case sf::Event::Closed:
		//set running to false
		running = false;
		break;

	//if the user pressed a mouse button
	case sf::Event::MouseButtonPressed:
		//if the button pressed was the left mouse button
		if (event.mouseButton.button == sf::Mouse::Left) {
			//check each button in the current menuState and execute related code if on button
			switch (menuState) {
			//if main menu
			case 0:
				//if the new game button was pressed
				if (buttons[0][0].contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					//start a new game
					player.score = 0;
					generateLevel(sf::Vector2i(3, 3), 8);
					//set the menustate to the game mode
					menuState = 1;
				}
				//if the options button was pressed
				if (buttons[0][1].contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					//change to the options menu
					menuState = 2;
				}
				//if the quit button was pressed
				if (buttons[0][2].contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					//set running to false
					running = false;
				}
				//if the player currently has a game running and the resume button was pressed
				if (playing && buttons[3][0].contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					//set the menu state to the game scene
					menuState = 1;
				}
				break;
			//if settings menu
			case 2:
				//if the back button was pressed
				if (buttons[2][2].contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					//change to the main menu
					menuState = 0;
				}
				//if the toggle fullscreen button was pressed
				if (buttons[2][3].contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					//toggle the fullscreen setting
					FULLSCREEN = !FULLSCREEN;
					altered = true;
				}
				//if get native resolution button pressed
				if (buttons[2][4].contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					//get the desktop resolution
					window.create(sf::VideoMode(RES_WIDTH, RES_HEIGHT), "Recoil", sf::Style::Close);
					sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
					//set the game resolution to the desktop resolution
					RES_HEIGHT = desktop.height;
					RES_WIDTH = desktop.width;
					altered = true;
				}
				//if a fixed resolution button was pressed
				if (buttons[2][5].contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					//set the game resolution to the specified resolution
					RES_HEIGHT = 900;
					RES_WIDTH = 1600;
					altered = true;
				}
				if (buttons[2][6].contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
					//set the game resolution to the specified resolution
					RES_HEIGHT = 720;
					RES_WIDTH = 1280;
					altered = true;
				}
				//if the settings were altered
				if (altered) {
					//update the screen settings
					hud.setSize(RES_WIDTH, RES_HEIGHT);
					camera.setSize(RES_WIDTH, RES_HEIGHT);
					hud.setCenter(RES_WIDTH / 2, RES_HEIGHT / 2);

					//if the fullscreen option is true
					if (FULLSCREEN) {
						//create a fullscreen window
						window.create(sf::VideoMode(RES_WIDTH, RES_HEIGHT), "Recoil", sf::Style::Fullscreen);
					}
					else {
						//otherwise, create a windowed window
						window.create(sf::VideoMode(RES_WIDTH, RES_HEIGHT), "Recoil", sf::Style::Close);
					}

					window.setFramerateLimit(FRAME_CAP);
					window.setVerticalSyncEnabled(true);	//enable v-sync to prevent screen tearing

					//adjust buttons
					buttons[2][2].buttonBox.move(RES_WIDTH - oldResX, RES_HEIGHT - oldResY);
					buttons[2][2].text.move(RES_WIDTH - oldResX, RES_HEIGHT - oldResY);
					buttons[0][0].buttonBox.move(RES_WIDTH - oldResX, 0);
					buttons[0][0].text.move(RES_WIDTH - oldResX, 0);
					buttons[0][1].buttonBox.move(RES_WIDTH - oldResX, 0);
					buttons[0][1].text.move(RES_WIDTH - oldResX, 0);
					buttons[0][2].buttonBox.move(RES_WIDTH - oldResX, 0);
					buttons[0][2].text.move(RES_WIDTH - oldResX, 0);

					//if there is a game in progress
					if (playing) {
						//adjust game background
						backDrop.setPosition(-RES_WIDTH, -RES_HEIGHT);
						backDrop.setTextureRect(sf::IntRect(0, 0, levelDimensions.x * CHUNK_WIDTH * TILE_SIZE + 2 * RES_WIDTH, levelDimensions.y * CHUNK_WIDTH * TILE_SIZE + 2 * RES_HEIGHT));
					}
				}
				break;
			//otherwise, go to the next pre-game screen
			default:
				++menuState;
				break;
			}
		}
		break;

	//if the user pressed a key
	case sf::Event::KeyPressed:
		//if on the pre-main menu screens
		if (menuState < 0) {
			//go to the next menu
			++menuState;
		}
		//if in the settings menu and escape is pressed
		if (event.key.code == sf::Keyboard::Escape && menuState == 2) {
			//go back to the main menu
			menuState = 0;
		}

	//if not any of the above events, do nothing
	default:
		break;
	}
}

void Recoil::menuLogic() {
	//reset clock
	deltaTime = clock.restart().asSeconds();

	//update each button in the current menu
	if (menuState >= 0) {
		for (vector<Button>::iterator it = buttons[menuState].begin(); it != buttons[menuState].end(); ++it) {
			it->update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		}

		//if on the main menu and there is a game running
		if (menuState == 0 && playing) {
			//update the resume button
			buttons[3][0].update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		}
	}
}

void Recoil::menuRender() {
	//clear the window
	window.clear();

	//use the hud view
	window.setView(hud);

	if (menuState >= 0) {
		//draw a background
		sf::Sprite background;
		background.setTexture(textures.terrain.backDrop);
		background.setTextureRect(sf::IntRect(0, 0, RES_WIDTH, RES_HEIGHT));
		window.draw(background);

		//for each button in the current menu
		for (vector<Button>::iterator it = buttons[menuState].begin(); it != buttons[menuState].end(); ++it) {
			//draw the button
			it->draw(window);
		}

		//if in the main menu and the player currently has a game
		if (menuState == 0 && playing) {
			//draw the resume game button to the screen
			buttons[3][0].draw(window);
		}
	} else {
		//if on the warning screen
		if (menuState == -1) {
			//load the warning screen
			sf::Sprite warning;
			warning.setTexture(textures.ui.warning);

			//scale it to fit the screen vertically and maintain ratio
			warning.setScale(RES_HEIGHT / warning.getLocalBounds().height, RES_HEIGHT / warning.getLocalBounds().height);

			//center the warning
			warning.setOrigin(warning.getLocalBounds().width / 2, warning.getLocalBounds().height / 2);
			warning.setPosition(RES_WIDTH / 2, RES_HEIGHT / 2);

			//draw the warning
			window.draw(warning);
		}
	}

	//update to the screen
	window.display();
}