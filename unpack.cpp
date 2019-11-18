//--q|DANIEL-_-CORCORAN|p---//
//This file will take the selected level and return all the in game objects, in a vector. 
//This does not include USER objects. It does not include the player object. It currently will contain the black holes. 

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <algorithm>


void loadfromfile(int level, std::vector<sf::Sprite> &asteroid, std::vector<sf::Sprite> &star, std::vector<int> &star_state, std::vector<sf::CircleShape> &massive, sf::Sprite &astronaut, sf::CircleShape &blackhole, int &mass, std::string &pre_message, std::string &astronaut_message) {
	int x = 0;
	int y;
	
	//Load all file from location in asset\	
	std::ifstream file;
	char filepath[30];
	sprintf_s(filepath, "assets\\levels\\level_%d.level", level);
	std::string data_filepath = std::string(filepath); //Convert char to str
	file.open(data_filepath);

	//Structure is basically this

//First section: Meta Data
//1. Define if we have a pre-level astronaut. True if true, false if false
//1a. If true, put string as one string, using underscores for spaces
//2. Mass allowance
//3. black hole position (x, y)
//4. astronaut position (x, y)
//5. astronaut string, encapsulated between " && "


//begin this section with "bgn", so we can align with the position for asteroid vector (makes debugging easier)
//Second section: Asteroid data;
//Just put x and y positions in succession and end this section with the word bgn. 

//Third section: Star data;
//star data is actually 3 values. X, Y, and bool Store. 
//So store these in this order, end the section with bgn. 

//Fourth section: Massive data;
//same as astroids, really

//I think that's everything....

	std::string begin_flag;
	std::string argument_pre_string;
	file >> argument_pre_string;

	if (argument_pre_string == "true") {
		file >> pre_message; //Collect astronaut string;
		std::replace(pre_message.begin(), pre_message.end(),'_', ' ');
		//TODO: Replace underscore with spaces;
	}
	file >> mass;
	int a, b, c, d;
	file >> a >> b >> c >> d;
	blackhole.setPosition(a, b);
	astronaut.setPosition(c, d);
	std::cout << "Astronaut vector: " << c << " " << d << std::endl; 
	file >> astronaut_message;
	std::replace(astronaut_message.begin(), astronaut_message.end(), '_', ' ');
	//file >> begin_flag;
	
	//SEQUENCE: bgn, asteroidx, asteroidy, ... 

	//---ASTEROID UNPACK---//
	while ((x != 999988)) {
		sf::Sprite pushback;
		file >> x >> y;
		if (x != 999988) {
			pushback.setPosition(x, y);
			pushback.setOrigin(25, 25);
			asteroid.push_back(pushback);
		}
		else {
			std::cout << "\nAsteroid vector collected\nsize " << asteroid.size() << std::endl;
			x = 0;
			break;
		}
	}


	//---STAR UNPACK---//
	while ((x != 999988)) {
		sf::Sprite pushback;
		file >> x >> y;
		if (x != 999988) {
			file >> a;
			pushback.setPosition(x, y);
			pushback.setOrigin(15, 15);
			//std::cout << "Pushback sprite\n";
			star.push_back(pushback);
			//std::cout << "pushback state\n";
			star_state.push_back(a);
		}
		else {
			std::cout << "\n Star vector collected\nsize " << star.size() << std::endl;
			x = 0;
			break;
		}
	}

	//---MASSIVE UNPACK---//
	while ((x != 999988)) {
		sf::CircleShape pushback;
		file >> x >> y;
		if (x != 999988) {
			std::cout << "flag\n";
			pushback.setRadius(70);
			pushback.setOrigin(35, 35);
			pushback.setPosition(x, y);
			std::cout << "x: " << x << "  y: " << y << std::endl;
			massive.push_back(pushback);
		}
		else {
			std::cout << "\nMassive vector collected\nsize " << massive.size() << std::endl;
			break;
		}
	}


	std::cout << "Success! All vectors loaded from file.";

}

std::vector<int> getStarState(int level) { //0 is uncollected. 1 is collected
	
		std::vector<int> vector;
		std::ifstream file;
		char filepath[34];
		sprintf_s(filepath, "assets\\levels\\star_%d.txt", level);
		std::string data_filepath = std::string(filepath); //Convert char to str
		file.open(data_filepath);
		int x, y, state, i;
		i = 0;
		while (file >> x >> y >> state) {

			vector.push_back(state);
			i++;
		}

		std::cout << "star boolean states loaded...\n";




		return vector;
	}
std::vector<sf::Sprite> createStarVector(int level) {
	std::vector<sf::Sprite> vector;
	sf::Sprite pushback;
	std::ifstream file;
	char filepath[34];
	sprintf_s(filepath, "assets\\levels\\star_%d.txt", level);
	std::string data_filepath = std::string(filepath); //Convert char to str
	file.open(data_filepath);
	int x, y, state, i;
	i = 0;
	while (file >> x >> y >> state) {

		vector.push_back(pushback);
		vector[i].setPosition(x, y);
		vector[i].setOrigin(15, 15);
		//vector[i].setRotation(rand() % 100); //Maybe change? idk
		i++;
	}

	std::cout << i << "stars loaded...\n";
	return vector;
}
int unpackStartingMass(int level) {
	int nil1, nil2, nil3;
	std::ifstream file;
	char filepath[30];
	sprintf_s(filepath, "assets\\levels\\level_%d.txt", level);
	std::string data_filepath = std::string(filepath); //Convert char to str
	file.open(data_filepath);

	file >> nil1 >> nil2 >> nil3;
	file.close();
	return nil3;



}
int currentStars(int level) {
	int sum = 0;
	std::ifstream file;
	char filepath[34];
	sprintf_s(filepath, "assets\\levels\\star_%d.txt", level);
	std::string data_filepath = std::string(filepath); //Convert char to str
	file.open(data_filepath);
	int x, y, state, i;
	i = 0;
	
	while (file >> x >> y >> state) {
		sum = sum + pow(0, state);
		i++;
	}

	std::cout << "star progress loaded\n";


	return sum;
}
sf::Vector2f getAstronautPosition(int level) {
	sf::Vector2f vector;
	std::ifstream file;
	char filepath[30];
	sprintf_s(filepath, "assets\\levels\\level_%d.txt", level);
	std::string data_filepath = std::string(filepath); //Convert char to str
	file.open(data_filepath);
	int nil1, nil2, nil3, nil4, nil5;
	file >> nil1 >> nil2 >> nil3 >> nil4 >> nil5 >>vector.x >> vector.y;
	std::cout << "astronaut vector: " << vector.x << std::endl << vector.y;
	file.close();
	return vector;


}
int showAstronaut(int level) {

	int val;
	std::ifstream file;
	char filepath[30];
	sprintf_s(filepath, "assets\\levels\\level_%d.txt", level);
	std::string data_filepath = std::string(filepath); //Convert char to str
	file.open(data_filepath);
	int nil1, nil2, nil3, nil4, nil5, nil6, nil7;
	file >> nil1 >> nil2 >> nil3 >> nil4 >> nil5 >> nil6 >> nil7 >> val;
	std::cout << "show astronaut val: " << val;
	file.close();
	return val;


}
std::string getMessage(int level) {
	sf::Vector2f vector;
	std::ifstream file;
	char filepath[30];
	sprintf_s(filepath, "assets\\levels\\level_%d.txt", level);
	std::string data_filepath = std::string(filepath); //Convert char to str
	file.open(data_filepath);
	int nil1, nil2, nil3, nil4, nil5, nil6, nil7, nil8;
	file >> nil1 >> nil2 >> nil3 >> nil4 >> nil5 >> nil6 >> nil7 >> nil8;
	std::string a;
	std::string b;
	while (std::getline(file, a)) {
		a.append("\n");
		b.append(a);
	};
	std::cout << a << std::endl;
	file.close();
	return b;



}


