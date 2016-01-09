//FileUtils.cpp

/*
This file contains a set of functions used in
both reading from and writing to files.
*/

#include "Utilities.h"

using namespace std;

/*
Note: the settings file will be structured in a very
strict manner, in order to ensure all data is read
correctly.
*/

//a file to read a pre-existing settings file and save those settings to be used in the game
bool FileUtils::loadSettings(string filename, int* res_width, int* res_height, bool* fullscreen) {
	string read;
	ifstream file;

	//attempt to open the file
	file.open(filename);

	//check if file is open
	if (file.is_open()) {
		//notify console settings file is present
		cout << "Loading settings from detected file: " << filename << endl;

		//read first string, convert to int and set to horizontal resolution
		getline(file, read);
		*res_width = (int)(stof(read));
		//repeat for resolution height
		getline(file, read);
		*res_height = (int)(stof(read));
		//notify console
		cout << "Settings: Resolution set to " << *res_width << "x" << *res_height << endl;

		//read next line, convert to a boolean and set to the fullscreen option
		getline(file, read);
		*fullscreen = (bool)(stof(read));
		//notify console
		(*fullscreen) ? (cout << "Settings: Fullscreen enabled" << endl) : (cout << "Settings: Fullscreen disabled" << endl);

		//close the file
		file.close();
	}
	else {
		//if not open, it doesn't exist
		//notify using console
		cout << "File not found: " << filename << endl;
		//load hardcoded settings
		cout << "Creating stock settings";
		*res_width = 1280;
		*res_height = 720;
		//notify via console
		cout << "Settings: Generated resolution of " << *res_width << "x" << *res_height << endl;
		//return false
		return false;
	}
}

//converts a string to a float
float FileUtils::stringToFloat(string string) {
	float result = stof(string);
	return result;
}