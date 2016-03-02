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
	//some driver code
	//will obviously be replaced with actual level generation
	char map0[5] = { 'd','d','d','d','d' };
	char map1[5] = { 'd',' ',' ',' ','d' };
	char map2[5] = { 'd',' ','d',' ','d' };
	vector<char> vmap0;
	vector<char> vmap1;
	vector<char> vmap2;
	vmap0.assign(map0, map0 + 5);
	vmap1.assign(map1, map1 + 5);
	vmap2.assign(map2, map2 + 5);
	vector<vector<char>> map;
	map.push_back(vmap0);
	map.push_back(vmap1);
	map.push_back(vmap2);
	map.push_back(vmap1);
	map.push_back(vmap0);
	
	return map;
}