//Button.h

/*
This file contains the button class,
which is used in the game menus.
*/

#include "Recoil.h"

class Button {
public:
	Button(sf::IntRect rect, sf::Color buttonColor, sf::Color highlightColor, std::string buttonText, int textAlign, sf::Font &font, int size, std::vector<std::vector<Button>> &buttons, int buttonIndex);

	//checks whether a point lies within the button or not
	bool contains(sf::Vector2f mousePos);

	//updates the button depending on mouse position, i.e button colour
	void update(sf::Vector2f mousePos);
	//draws the button to the screen
	void draw(sf::RenderWindow &window);

	sf::Color buttonColor;
	sf::Color highlightColor;
	sf::RectangleShape buttonBox;
	sf::Text text;
};