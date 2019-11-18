#include "pch.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "unpack.h"
#include <SFML/Graphics.hpp>
void newmaxlevel(int level) {
	//This function will overwrite the max level data file...
	std::ofstream file;

	file.open("assets\\data\\maxlevel.txt", std::ios::trunc);
	file << level + 1;
	file.close();
}
int getmaxlevel() {
	std::ifstream file;

	file.open("assets\\data\\maxlevel.txt");
	int level; 
	file >> level;
	file.close();



	return level;

}
