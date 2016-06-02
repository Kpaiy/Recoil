//Init.cpp

/*
This file contains the code for loading all assets
for use in the game. If something goes wrong, this
function will return false, ceasing running of the
game.
*/

#include "Recoil.h"

using namespace std;

bool Recoil::Init() {
	//declare constants
	TILE_SIZE = 50;
	CHUNK_WIDTH = 25;

	FRAME_CAP = 75;

	GRAVITY = 4.2;

	CONSIDER_RANGE = 1.2;
	PROJECTILE_RANGE = 0.4;

	//set a seed for random generation
	srand(time(0));

	//load settings
	FileUtils::loadSettings(string("settings.cfg"), RES_WIDTH, RES_HEIGHT, FULLSCREEN);
	cout << "----------------------" << endl;

	//assign variable values here and load assets
	
	//load textures
	textures.load();

	//load chunks
	loadAllChunks("chunks.rcl", CHUNK_WIDTH);

	//load sprites
	//temporary things
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
	
	//level setup
	int chunkHorizontal = 3;		//count of horizontal chunks in the level to be generated
	int chunkVertical = 3;			//count of vertical chunks
	generateLevel(sf::Vector2i(3, 3), 10);
	//backdrop setup
	backDrop.setTexture(textures.terrain.backDrop);
	backDrop.setPosition(-RES_WIDTH, -RES_HEIGHT);
	backDrop.setTextureRect(sf::IntRect(0, 0, chunkHorizontal * CHUNK_WIDTH * TILE_SIZE + 2 * RES_WIDTH, chunkVertical * CHUNK_WIDTH * TILE_SIZE + 2 * RES_HEIGHT));

	//temporary player constructor
	player = Player(sf::Vector2f((float)500, (float)500), tempAnimations, tempWeaps);
	player.friction = 0;
	//player movement trackers
	jump = false;
	fire = false;

	//temporary enemy test
	vector<sf::Texture*> enemyTex;
	enemyTex.push_back(&textures.enemies.wraith);
	vector<vector<sf::Texture*>> enemyAnims;
	enemyAnims.push_back(enemyTex);
	
	Enemy(sf::Vector2f((float)500, (float)2500), enemies, enemyAnims, &textures.projectiles.pistol);

	//setup projectile container
	vector<Projectile> tempProjectiles;
	projectiles.push_back(tempProjectiles);
	projectiles.push_back(tempProjectiles);

	//console shenanigans
	cout << "Opening window..." << endl;

	//if the fullscreen option is true
	if (FULLSCREEN) {
		//create a fullscreen window
		window.create(sf::VideoMode(RES_WIDTH, RES_HEIGHT), "Recoil", sf::Style::Fullscreen);
	}
	else {
		//otherwise, create a windowed window
		window.create(sf::VideoMode(RES_WIDTH, RES_HEIGHT), "Recoil");
	}

	//set up the game camera
	camPos = player.center();
	camDamp = 0.1;
	camera.setSize(RES_WIDTH, RES_HEIGHT);
	camera.setCenter(camPos);
	window.setView(camera);	
	window.setFramerateLimit(FRAME_CAP);
	window.setVerticalSyncEnabled(true);	//enable v-sync to prevent screen tearing
	offset = sf::Vector2f(0,0);
	dampRate = 75;
	camCounter = 0;

	hud.setSize(RES_WIDTH, RES_HEIGHT);
	hud.setCenter(RES_WIDTH / 2, RES_HEIGHT / 2);
	

	menuState = 0;
	playing = false;

	//disable os repeating keystrokes when a key is held down
	window.setKeyRepeatEnabled(false);

	//if no hiccups from the first bit, return true
	return true;
}