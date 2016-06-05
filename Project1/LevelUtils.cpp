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
			//if a solid dirt tile
			case 'd':
				//create a dirt tile
				//multiply list index by TILE_SIZE to obtain coordinates
				Tile(textures.terrain.dirt, sf::Vector2f((float)x * TILE_SIZE, (float)y * TILE_SIZE), tiles);
				break;
			//if a non-solid dirt tile
			case 'D':
				//create the tile
				Tile(textures.terrain.dirt, sf::Vector2f((float)x * TILE_SIZE, (float)y * TILE_SIZE), decor);
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

/*
This function takes in two numbers, the width and height of the level
in chunks. This function then stitches together the appropriate amount
and types of chunks together to fit the dimensions, creating a level.
*/
vector<vector<char>> Recoil::generateMap(sf::Vector2i dimensions) {	
	//a temporary chunk used for stitching purposes
	vector<vector<char>> tempChunk;
	//the output level
	vector<vector<char>> level;

	//for each y chunk in dimensions
	for (int y = 0; y != dimensions.y; y++) {
		//iterate through x values
		for (int x = 0; x != dimensions.x; x++) {
			//if the first element in the row
			if (x == 0) {
				//pick a random chunk of suitable type
				//if in the top left corner
				if (y == 0) {
					//pick a random top-left chunk
					tempChunk = randChunk(chunk7);
				} else if (y == dimensions.y - 1) {
					//if along the bottom left
					//pick a random bottom-left chunk
					tempChunk = randChunk(chunk1);
				} else {
					//otherwise, it is of orientation middle-left
					//pick a random middle-left chunk
					tempChunk = randChunk(chunk4);
				}
				//append the chunk to the level container
				for (vector<vector<char>>::iterator row = tempChunk.begin(); row != tempChunk.end(); ++row) {
					//append row by row to the level
					level.push_back(*row);
				}
			} else {
				//if chunk is not first chunk in row
				//if last chunk in row of chunks
				if (x == dimensions.x - 1) {
					//if on the top-right
					if (y == 0) {
						//pick a random top-right chunk
						tempChunk = randChunk(chunk9);
					} else if (y == dimensions.y - 1) {
						//if along the bottom right
						//pick a random bottom-right chunk
						tempChunk = randChunk(chunk3);
					} else {
						//otherwise, it is of orientation middle-right
						//pick a random middle-right chunk
						tempChunk = randChunk(chunk6);
					}
				} else {
					//otherwise, is not along either left or right edge
					//if on the top-middle
					if (y == 0) {
						//pick a random top-middle chunk
						tempChunk = randChunk(chunk8);
					} else if (y == dimensions.y - 1) {
						//if along the bottom-middle
						//pick a random bottom-middle chunk
						tempChunk = randChunk(chunk2);
					} else {
						//otherwise, it is of orientation middle-middle
						//pick a random middle-middle chunk
						tempChunk = randChunk(chunk5);
					}
				}
				//iterate through each row of the chunk to add
				for (int row = 0; row != tempChunk.size(); ++row) {
					//iterate through each char
					for (int tile = 0; tile != tempChunk[y].size(); ++tile) {
						//append the char to the appropriate row
						level[row + (y * CHUNK_WIDTH)].push_back(tempChunk[row][tile]);
					}
				}
			}
		}

	}

	return level;
}

//returns a random chunk from a list of chunks
vector<vector<char>> Recoil::randChunk(vector<vector<vector<char>>> chunkType) {
	//pick a random number between zero and the size of the container - 1
	int random = rand() % chunkType.size();
	//return the chunk with the corresponding index in the chunk container
	return chunkType[random];
}

void Recoil::generateEnemies(sf::Vector2i dimensions, int enemies) {
	vector<sf::Texture*> enemyTex;
	enemyTex.push_back(&textures.enemies.wraith);
	vector<vector<sf::Texture*>> enemyAnims;
	enemyAnims.push_back(enemyTex);
	
	//for the amount of times specified by enemies
	for (int i = 0; i < enemies; ++i) {
		//randomly generate a spawnPos that lies within the map
		sf::Vector2f spawnPos;
		spawnPos.x = rand() % (dimensions.x * TILE_SIZE * CHUNK_WIDTH);
		spawnPos.y = rand() % (dimensions.y * TILE_SIZE * CHUNK_WIDTH);

		//create an enemy at this location
		Enemy(spawnPos, this->enemies, enemyAnims, &textures.projectiles.pistol);
	}
}

void Recoil::generateLevel(sf::Vector2i dimensions, int enemies) {
	//save the player's score
	int score = player.score;

	//reset the tile, enemy, and projectile containers
	tiles.clear();
	this->enemies.clear();
	projectiles.clear();
	//setup projectile container
	vector<Projectile> tempProjectiles;
	projectiles.push_back(tempProjectiles);
	projectiles.push_back(tempProjectiles);

	generateTiles(generateMap(dimensions));
	generateEnemies(dimensions, enemies);

	//create the player at the bottom middle of the map
	//player setup
	missingSprite.setTexture(textures.misc.missing);
	vector<sf::Texture*> tempVec;
	tempVec.push_back(&textures.player.idle);
	vector<vector<sf::Texture*>> tempAnimations;
	tempAnimations.push_back(tempVec);
	
	vector<Weapon> tempWeaps;
	
	vector<sf::Texture*> f;
	f.push_back(&textures.player.fGun);
	vector<sf::Texture*> b;
	b.push_back(&textures.player.bGun);
	vector<vector<sf::Texture*>> fGun;
	fGun.push_back(f);
	vector<vector<sf::Texture*>> bGun;
	bGun.push_back(b);

	tempWeaps.push_back(Weapon("Dual Pistols", textures.projectiles.pistol, &textures.projectiles.pistol, fGun, bGun));

	//player constructor
	player = Player(sf::Vector2f(dimensions.x * CHUNK_WIDTH * TILE_SIZE / 2, dimensions.y * CHUNK_WIDTH * TILE_SIZE - 100), tempAnimations, tempWeaps, 100, 100, score);
	player.friction = 0;
	//player movement trackers
	jump = false;
	fire = false;

	//setup the backdrop
	backDrop.setTexture(textures.terrain.backDrop);
	backDrop.setPosition(-RES_WIDTH, -RES_HEIGHT);
	backDrop.setTextureRect(sf::IntRect(0, 0, dimensions.x * CHUNK_WIDTH * TILE_SIZE + 2 * RES_WIDTH, dimensions.y * CHUNK_WIDTH * TILE_SIZE + 2 * RES_HEIGHT));

	//camera setup
	camPos = player.center();
	offset = sf::Vector2f(0, 0);

	playing = true;
}