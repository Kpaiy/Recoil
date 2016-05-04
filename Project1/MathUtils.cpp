//MathUtils.cpp

/*
Contains useful math functions.
*/

#pragma once

#include "Utilities.h"

//takes a vector and returns a normalised vector, with the same direction, but a magnitude of 1
sf::Vector2f MathUtils::normalize(sf::Vector2f vector) {
	float length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));

	sf::Vector2f result;
	//divide the components of the vector by the magnitude
	result.x = vector.x / length;
	result.y = vector.y / length;

	//return the result
	return result;
}

//finds the angle of the second point relative to the first in degrees
float MathUtils::findAngle(sf::Vector2f origin, sf::Vector2f target) {
	float result = atan2(target.x - origin.x, target.y - origin.y) * 180/PI;

	return result;
}
