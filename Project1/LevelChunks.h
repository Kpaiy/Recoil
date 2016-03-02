//LevelChunks.h

/*
This class structure will hold all level 
chunks required to stitch together during 
random generation of levels.
*/

#include "Utilities.h"

class LevelChunks {
public:
	LevelChunks();
	bool load(std::string filename, int chunkWidth);
	void loadChunk(std::vector<std::vector<std::vector<char>>> &chunkContainer, std::ifstream &file, std::string &tempString);

	//containers for different types of terrain chunks
	//named based on typical position in level layout
	/*
	Chunk containers are classed based their position on the
	numpad after the keyword "chunk"

	789			i.e chunk7 contains tiles designed to fit 
	456			in the top left of a level or otherwise
	123
	*/

	std::vector<std::vector<std::vector<char>>> chunk1;
	std::vector<std::vector<std::vector<char>>> chunk2;
	std::vector<std::vector<std::vector<char>>> chunk3;
	std::vector<std::vector<std::vector<char>>> chunk4;
	std::vector<std::vector<std::vector<char>>> chunk5;
	std::vector<std::vector<std::vector<char>>> chunk6;
	std::vector<std::vector<std::vector<char>>> chunk7;
	std::vector<std::vector<std::vector<char>>> chunk8;
	std::vector<std::vector<std::vector<char>>> chunk9;
};