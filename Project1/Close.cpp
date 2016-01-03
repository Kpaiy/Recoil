//Close.cpp

/*
This code will perform any cleanup or saving
required when the user closes the game.
*/

#include "Recoil.h"

using namespace std;

void Recoil::Close() {
	//close the window
	window.close();
	//pause the console (WINDOWS ONLY)
	system("pause");
}