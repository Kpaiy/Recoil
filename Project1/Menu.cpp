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
		text.setOrigin(0, textDimensions.height / 2);
		//position text
		text.setPosition(boxBounds.left + textOffset, boxBounds.top + boxBounds.height / 2);
	}
	//if aligbn center
	else if (textAlign == 0) {
		//set the origin to the center of the text
		text.setOrigin(textDimensions.width / 2, textDimensions.height / 2);
		//position text
		text.setPosition(boxBounds.left + boxBounds.width / 2, boxBounds.top + boxBounds.height / 2);
	}
	//otherwise, align right
	else {
		//set the origin to the middle right
		text.setOrigin(textDimensions.width, textDimensions.height / 2);
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
					generateLevel(sf::Vector2i(4, 3), 12);
					//set the menustate to the game mode
					menuState = 1;
				}
				break;
			//if settings menu
			case 2:
				break;
			//otherwise, do nothing
			default:
				break;
			}
		}
		break;

	//if not any of the above events, do nothing
	default:
		break;
	}
}

void Recoil::menuLogic() {
	//reset clock
	deltaTime = clock.restart().asSeconds();

	//update each button in the current menu
	for (vector<Button>::iterator it = buttons[menuState].begin(); it != buttons[menuState].end(); ++it) {
		it->update(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	}
}

void Recoil::menuRender() {
	//clear the window
	window.clear();

	//use the hud view
	window.setView(hud);

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

	//update to the screen
	window.display();
}