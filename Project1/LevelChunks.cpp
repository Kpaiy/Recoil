/*

//LevelChunks.cpp

/*
Contains functions related to the structuring
of the LevelChunks class containing
two dimensional arrays related to random
level generation.
*/

#include "Recoil.h"

using namespace std;

LevelChunks::LevelChunks() {

}

//loads the chunks file into this class structure
bool LevelChunks::load(string filename, int chunkWidth) {
	//declare input file
	ifstream file;
	
	//attempt to open the file
	file.open(filename);

	//check if the file is open
	if (file.is_open()) {
		//notify console
		cout << "Loading chunks from detected file: " << filename << endl;

		//create temp string
		string tempString;
		//first read
		file >> tempString;
		
		//load each chunk
		loadChunk(chunk1, file, tempString);
		loadChunk(chunk2, file, tempString);
		loadChunk(chunk3, file, tempString);
		loadChunk(chunk4, file, tempString);
		loadChunk(chunk5, file, tempString);
		loadChunk(chunk6, file, tempString);
		loadChunk(chunk7, file, tempString);
		loadChunk(chunk8, file, tempString);
		loadChunk(chunk9, file, tempString);

		//close the file
		file.close();

		//if nothing went wrong, return true
		return true;
		
	}
	else {
		//notify console
		cout << "File not found: " << filename << endl;
		return false;
	}
}

void LevelChunks::loadChunk(vector<vector<vector<char>>> &chunkContainer, ifstream &file, string &tempString) {
	//create temporary vectors
	vector<vector<char>> chunk;
	vector<char> tempVector;

	//while not reading a hash which denotes the end of a chunk type
	while (tempString != "#") {
		//append the row to the chunk
		tempVector.assign(tempString.begin(), tempString.end());
		chunk.push_back(tempVector);
		//prepare next read
		file >> tempString;
		//if the read is an exclamation mark which denotes the end of a chunk
		if (tempString == "!") {
			//append the two dimensional char vector to the corresponding chunk type container
			chunkContainer.push_back(chunk);
			//reset the chunk vector
			chunk.clear();
			//prepare the next read
			file >> tempString;
		}
	}
}