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

//a function to read a pre-existing settings file and save those settings to be used in the game
bool FileUtils::loadSettings(string filename, int& res_width, int& res_height, bool& fullscreen) {
	string read;
	ifstream file;

	//attempt to open the file
	file.open(filename);

	//check if file is open
	if (file.is_open()) {
		//notify console settings file is present
		cout << "Loading settings from detected file: " << filename << endl;

		//load values from file into respective variables
		file >> res_width >> res_height >> fullscreen;

		//notify console
		cout << "Settings: Resolution set to " << res_width << "x" << res_height << endl;
		(fullscreen) ? (cout << "Settings: Fullscreen enabled" << endl) : (cout << "Settings: Fullscreen disabled" << endl);

		//close the file
		file.close();

		return true;
	}
	else {
		//if not open, it doesn't exist
		//notify using console
		cout << "File not found: " << filename << endl;
		//load hardcoded settings
		cout << "Creating stock settings";
		res_width = 1280;
		res_height = 720;
		//notify via console
		cout << "Settings: Generated resolution of " << res_width << "x" << res_height << endl;
		//return false
		return false;
	}
}

//a function to save the current settings to a settings file
bool FileUtils::saveSettings(string filename, int& res_width, int& res_height, bool& fullscreen) {
	ofstream file;

	//notify console
	cout << "Saving settings..." << endl;

	//attempt to access file
	file.open(filename);

	//check if file is open for writing
	if (file.is_open()) {
		//write variables to file
		file << res_width << endl << res_height << endl << fullscreen;
		//notify that settings were saved
		cout << "Settings saved to file: " << filename << endl;

		return true;
	}
	else {
		//if unable to write to file, notify console
		cout << "Unable to write to file: " << filename << endl;
		cout << "Unable to save settings" << endl;

		return false;
	}
}

//converts a string to a float
float FileUtils::stringToFloat(string string) {
	float result = stof(string);
	return result;
}