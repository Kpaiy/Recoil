//LevelUtils.cpp

/*
This file contains subroutines related to the
generation of game levels.
*/

#include "Utilities.h"

using namespace std;

bool Recoil::generateTiles(vector<vector<char>> map) {
	//iterate through y values of map
	for (int y = 0; y < map.size(); ++y) {
		//iterate through x values of y value
		for (int x = 0; x < map[y].size(); ++x) {
			//check for characters representing tiles
			switch (map[y][x]) {
			//if a dirt tile
			case 'd':
				//create a dirt tile
				//multiply list index by TILE_SIZE to obtain coordinates
				Tile(textures.terrain.dirt, sf::Vector2f((float)x * TILE_SIZE, (float)y * TILE_SIZE), tiles);
				break;
			default:
				//if none of the above characters, do nothing
				break;
			}
		}
	}

	//if there are no problems, return true
	return true;
}

vector<vector<char>> Recoil::generateLevel() {
	//stupid stub code
	vector<vector<char>> dummy;
	char dumber[] = {'d','d','d','d','d'};
	vector<char> dumbest(dumber, dumber + 5);
	dummy.push_back(dumbest);
	dummy.push_back(dumbest);
	
	return dummy;
}