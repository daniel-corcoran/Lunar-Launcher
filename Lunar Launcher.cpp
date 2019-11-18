// q|DANIEL-_-CORCORAN|p




//Entry point for the Lunar Launcher Application. Written February 2019 by Daniel P. Corcoran

//LUNAR LAUNCHER 0.5 ENGINE LOADER
//Structure

//1. Main calls MainMenu. MainMenu Calls FunctionApplication.

//2. Level Returns INT Level# to game process thru main()

//3. Gameprocess calls class gameobject for game sprites

//4. Gameobject refers to unpack.cpp, which loads the parameters for created objects and 
	//level parameters... These POINTERS are forwared to the process.cpp, which returns 
	//Boolean Values. LevelUpdate modifies the player progress file, located in assets/data/progress.bin 
	//This is all subject to change. It mostly depends on how modular I want this to be, 

//TODO: Create toolbox
//TODO: Finish LevelConstructor (done? add massives)

//TODO: Finish Sprites
//TODO: Finish Menu Setting Parameter Implications... see /assets/parameters


//Stretch Goals: 



#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <math.h>
#include <fstream>
#include <vector>
#include "process.h"
#include "menufunction.h"
#include "savedata.h"
#include <filesystem>
#include <time.h>
#include <stdlib.h>
#include <string>


#define PI 3.141592653
bool DEBUG_GLOBAL = true; //False if false!
void musicHandler(sf::Music &music) {
	int num_of_songs = 2; 
	
	
	namespace fs = std::experimental::filesystem; 

//if music is playing, do nothing
	//Else, find a random song and start it
	if (music.getStatus() != sf::Music::Status::Playing) {
		std::string dir = "assets/sound/music/";
		srand(time(NULL));
		int songNumber = rand() % num_of_songs + 1; 
		dir += std::to_string(songNumber);
		dir += ".wav";
		if (!music.openFromFile(dir)) {
			std::cout << "Cant load music...";
		}
		music.play();

	}
}

void clearscreen(sf::RenderWindow& window) {

	int alpha = 0;
	sf::Time targetTime = sf::seconds(1);
	sf::Clock timer;
	sf::RectangleShape clearblock(sf::Vector2f(1920, 1080)); //initialize the black screen rectangle
	clearblock.setFillColor(sf::Color::Black);

	while (window.isOpen())
	{
		if (alpha > 50) {
			return;
		}
		clearblock.setFillColor(sf::Color(0, 0, 0, alpha));
		alpha = alpha +2;
		
		window.draw(clearblock);
		
		window.display();
	}

	   	 
}
void console() {
	std::cout << "Lunar Launcher 0.5.1 Game Engine";
	std::cout << "\n Written by Daniel P. Corcoran. Please do not copy for any reason.\n";
		std::cout << "q|DANIEL-_-CORCORAN|p\n";

}


//This is the game object vector constructor that passes a vector of sprites to the process.cpp (thread 2)
class gameobject {
public: 
	//Parametrized Constructor
	void setLevel(int level);
	//std::

private:
	//Call level sprite vector from unpack.cpp
	//std::vector<sf::Sprite> = unpack(level);

};
bool iswithin(int x, sf::Vector2i xrange) {//Is the value within the range?
	int xmin = xrange.x;
	int xmax = xrange.y; //this is really just the xmax value. Vector range is [xmin, xmax]...

	if ((x >= xmin) && (x <= xmax)) {
		return true; //if the button was pressed in this range!
	}
	return false;


}
int maxlevel() { //this function determines the maximum level the player can do... This probably should 
	int max = 1;
	std::ifstream inFile;
	inFile.open("assets\\data\\maxlevel.txt", std::ios::in);

	inFile >> max;
	if (DEBUG_GLOBAL == false) {
		std::cout << "Max level available: " << max << std::endl;
	}
	
	return max;
}

int levelbutton(sf::Vector2i position) {
	int level = 0;

	//Total X-Range of buttons is from 550 to 1390
	//Top Row y-range is 360 to 500
	//Bottom Row y-range is 530 to 680
	if (iswithin(position.x, sf::Vector2i(515, 1421))) { //check if the click happened in the window
		if (DEBUG_GLOBAL == false) {
			std::cout << std::endl << "This click is within the button range" << std::endl;
		}
		if (iswithin(position.y, sf::Vector2i(360, 500))) {
			if (DEBUG_GLOBAL == false) {
				std::cout << "User clicked a button on the top row" << std::endl;
			}
			//TOP ROW BUTTOM IF STATEMENTS (1-5)
			if (iswithin(position.x, sf::Vector2i(544, 684))) {
				return 1;
			}
			if (iswithin(position.x, sf::Vector2i(721, 864))) {
				return 2;
			}
			if (iswithin(position.x, sf::Vector2i(899, 1040))) {
				return 3;
			}
			if (iswithin(position.x, sf::Vector2i(1075, 1217))) {
				return 4;
			}
			if (iswithin(position.x, sf::Vector2i(1252, 1391))) {
				return 5;
			}


		}
		else if (iswithin(position.y, sf::Vector2i(530, 680))) {
			if (DEBUG_GLOBAL == false) {
				std::cout << "User clicked a button on the bottom row" << std::endl;
			}
			//BOTTOM ROW BUTTON IF STATEMENTS (6-10)
			if (iswithin(position.x, sf::Vector2i(544, 684))) {
				return 6;
			}
			if (iswithin(position.x, sf::Vector2i(721, 864))) {
				return 7;
			}
			if (iswithin(position.x, sf::Vector2i(899, 1040))) {
				return 8;
			}
			if (iswithin(position.x, sf::Vector2i(1075, 1217))) {
				return 9;
			}
			if (iswithin(position.x, sf::Vector2i(1252, 1391))) {
				return 10;
			}


		}
	
	}
	else {
		return -1;//Return to home screen? 
	}

	return level;
}
std::vector<sf::Sprite> levelmenu_objects(sf::Texture& numbers, int max) {
//This returns a vector of numbers, astronauts, etc that 
	std::vector<sf::Sprite> objects;
	for (int i = 0; i < 10; i++) { // We cycle through the ten levels, assigning sprites to the vector based on the players progress.
		int xsprite; //solution!
		if (i < max) { xsprite = 100 * i; }//if the level is allowed
		if (i >= max) { xsprite = 1000; } //otherwise we reference the lock portion of the number sprite
		
		
		
		
		sf::Sprite tempnum(numbers, sf::IntRect(xsprite, 0, 100, 100));
	//sf::Texture numbers;
				
	
	
	if (i < 5) { //Top rows of levels
		
		
		tempnum.setPosition(567+ 177*(i), 200 + 165 + 20); //Included numbers for clarity...
		objects.push_back(tempnum);
		
	}
	else { //Bottom rows of levels
		
		
		tempnum.setPosition(515 + 25 + 24 + 177 * (i-5), 200 + 165 + 20+140+25); //Included numbers for clarity...
		objects.push_back(tempnum);
			   		 
	}
	   	   	 
}


return objects;



}
//Below are game tools, not main loop things
void gameprocess(int level, sf::RenderWindow& window, sf::Music& music) { //This process facilitates communication between the game engine, the level selection, and the save files. 
	if (level == 0) { return; }

	//Fade out the screen when level is selected
	clearscreen(window);
	process(level, window, music);

}

int levelselector(sf::RenderWindow& window, sf::RectangleShape menu, sf::RectangleShape &background1, sf::RectangleShape &background2)
	{
	sf::Sprite cursor;
	sf::Texture cursorImg;
	cursorImg.loadFromFile("assets/textures/sprites/cursor.png");
	cursor.setTexture(cursorImg);

	int level = 0; 
	bool levelselected = false;
	//First thing is to take the main menu and transform it into the blank texture
	sf::Texture blankmenu;

	if (!blankmenu.loadFromFile("assets/textures/MainScreen/transition-texture.png"))
	{
		if (DEBUG_GLOBAL == false) {
			std::cout << "Error loading the menutexture in funtion mainmenu() " << std::endl;
		}
	}
	menu.setTexture(&blankmenu);
	window.clear();
	window.draw(background1);
	window.draw(background2);
	//menu.setFillColor(sf::Color::Black);
	//window.draw(menu);
	sf::Vector2f menudimensions = menu.getSize();
	//Expand menu size from 440,731 to 950,530 and change origin from 30,200 to 515, 200
	for(int i = 0; i < 5; i++) { //Change dimensions and position in 5 frames
	//
		float newxs = menu.getSize().x +102 ;
		float newys = menu.getSize().y -36 ;
		menu.setSize(sf::Vector2f(newxs, newys));
		menu.move(sf::Vector2f(90, 0));
		


		{//Smooth Background Scrolling
			if (background1.getPosition().x < -1919) {
				background1.setPosition(sf::Vector2f(1920, 0));
			}
			background1.move(sf::Vector2f(-1, 0));
			if (background2.getPosition().x < -1919) {
				background2.setPosition(sf::Vector2f(1920, 0));
			}
			background2.move(sf::Vector2f(-1, 0));
		}


		cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

		window.clear();
		window.draw(background1);
		window.draw(background2);
		window.draw(menu);
		window.draw(cursor);
		
		window.display();


	}
	
	
	
	float frames = 0; //frame counter
	sf::Texture levelselectiontexture;
	if (!levelselectiontexture.loadFromFile("assets/textures/MainScreen/level-select.png"))
	{
		if (DEBUG_GLOBAL == false) {
			std::cout << "Error loading the levelselectiontexture in funtion levelselection() " << std::endl;
		}
	}
	sf::RectangleShape levelmenu(sf::Vector2f(951.0, 549.0));
	levelmenu.setTexture(&levelselectiontexture);
	levelmenu.setPosition(515.0, 200.0);
	sf::Event event;
	sf::Texture numbers;
	sf::Texture lock;
	if (!numbers.loadFromFile("assets/textures/sprites/numbers.png"))
	{
		if (DEBUG_GLOBAL == false) {
			std::cout << "Error loading the levelselectiontexture in funtion levelselector " << std::endl;
		}
	}

	std::vector<sf::Sprite> levelmenusprites = levelmenu_objects(numbers, maxlevel());
	if (DEBUG_GLOBAL == false) {
		std::cout << "\n Sprites loaded from levelmenusprite vector \n size is: " << levelmenusprites.size() << std::endl;
	}


	while (window.isOpen()) {


		while (levelselected == false) {
			frames = frames + 0.0005;
			//std::cout << frames;
			//Smooth Background Scrolling
			{
				if (background1.getPosition().x < -1919) {
					background1.setPosition(sf::Vector2f(1920, 0));
				}
				background1.move(sf::Vector2f(-1, 0));
				if (background2.getPosition().x < -1919) {
					background2.setPosition(sf::Vector2f(1920, 0));
				}
				background2.move(sf::Vector2f(-1, 0));
				levelmenu.move(0, .05*sin((180 / PI) * frames)); //slowly move the menu to give a floating/breathing effect
				for (int i = 0; i < 10; i++) {
					levelmenusprites[i].move(0, .05*sin((180 / PI) * frames));


				}
			
			
			}
			while (window.pollEvent(event)) //Within this loop we might be able to change the 
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						return 0; 

					}
					

				}
				sf::Vector2i mousepos;
				if (event.type == sf::Event::MouseButtonPressed) {
					mousepos = sf::Mouse::getPosition();
					if (DEBUG_GLOBAL == false) {
						std::cout << "\n____________\n";
						std::cout << "\nMouse X: " << mousepos.x;
						std::cout << "\nMouse Y: " << mousepos.y;
					}
					int chosen = levelbutton(mousepos);
					
					if (chosen > 0 && (chosen <= maxlevel())) {
						if (DEBUG_GLOBAL == false) {
							std::cout << "User picked level number: " << chosen << std::endl;
						}
						return chosen;
					}
					else if (chosen == -1) { return 0; }
				}

			}
		



			window.clear();
			window.draw(background1);
			window.draw(background2);
			window.draw(levelmenu);
			for (int i = 0; i < levelmenusprites.size(); i++) {
				window.draw(levelmenusprites[i]);


			}
			cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
			window.draw(cursor);

			window.display();

		}



	}


	return level;
}

void mainmenu(sf::RenderWindow& window, sf::Music& music) {
	sf::Sprite cursor;
	sf::Texture cursorImg;
	cursorImg.loadFromFile("assets/textures/sprites/cursor.png");
	cursor.setTexture(cursorImg);
	
	
	
	window.setFramerateLimit(60);
	sf::RectangleShape background1(sf::Vector2f(1920, 1080));//We will scroll between two background images... when one goes off the screen it 
	//Will reappear at the right side and keep scrolling. 
	sf::RectangleShape background2(sf::Vector2f(1920, 1080)); //Other bg thing

	sf::RectangleShape menu(sf::Vector2f(440, 731));


	sf::Texture backgroundtexture;
	sf::Image menuimage;
	if (!backgroundtexture.loadFromFile("assets/textures/MainScreen/backgroundtexture.png"))
	{
		std::cout << "Error loading the backgroundtexture in funtion mainmenu() " << std::endl;
	}
	if (!menuimage.loadFromFile("assets/textures/MainScreen/menu-texture-carbon.png"))
	{
		std::cout << "Error loading the menutexture in funtion mainmenu() " << std::endl;
	}
	//menuimage.createMaskFromColor(sf::Color::White);

	sf::Texture menutexture;
	menutexture.loadFromImage(menuimage);

	background1.setTexture(&backgroundtexture);
	background1.setPosition(0, 0);
	
	background2.setTexture(&backgroundtexture);
	background2.setPosition(1920, 0);


	menu.setFillColor(sf::Color(255, 255, 255, 255));
	menu.setTexture(&menutexture);
	menu.setPosition(30, 200);

	sf::Vector2i mousepos;

	float frames = 0;
	sf::Event event;
	//Let's declare the position of all the button Y ranges
	sf::Vector2i buttonXRange(130, 345);  //These are the minimum and maximum x values the buttons fall within on the main menu
	sf::Vector2i StartYRange(502, 568);
	sf::Vector2i SettingsYRange(605, 675);
	sf::Vector2i HelpYRange(710, 778);
	sf::Vector2i ExitYRange(813, 890);
	 




	while (window.isOpen())
	{
		frames = frames + 0.001;
		while (window.pollEvent(event)) //Within this loop we might be able to change the 
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					//clearscreen(window);
					window.close();
					//clearscreen(&window);

				}
				if (event.key.code == sf::Keyboard::BackSpace) {
					for (int i = 1; i < 6; i++) {
						//resetStars(i);



					}
					newmaxlevel(0); //Reset max level to 1




				}


			}
			if (event.type == sf::Event::MouseButtonPressed) {
				mousepos = sf::Mouse::getPosition();
				if (DEBUG_GLOBAL == false) {
					std::cout << "\n____________\n";
					std::cout << "\nMouse X: " << mousepos.x;
					std::cout << "\nMouse Y: " << mousepos.y;
				}
				//Now for the fun if statements...

				if (iswithin(mousepos.x, buttonXRange)) { //If the button falls within these ranges
					if (iswithin(mousepos.y, StartYRange)) {
						std::cout << "\nStart Game";
						gameprocess(levelselector(window, menu, background1, background2), window, music);


					}else if (iswithin(mousepos.y, SettingsYRange)) {
						//Settings Menu
						std::cout << "\nSettings";


					}else if(iswithin(mousepos.y, HelpYRange)) {

						//Help Menu
						std::cout << "\nHelp";

					}
					else if (iswithin(mousepos.y, ExitYRange)) {
						std::cout << "\nExit";
						std::exit(EXIT_SUCCESS);

						//Exit Option
					}
				}







			}

		}




			{//Smooth Background Scrolling
				if (background1.getPosition().x < -1919) {
					background1.setPosition(sf::Vector2f(1920, 0));
				}
				background1.move(sf::Vector2f(-1, 0));
				if (background2.getPosition().x < -1919) {
					background2.setPosition(sf::Vector2f(1920, 0));
				}
				background2.move(sf::Vector2f(-1, 0));
				menu.move(sf::Vector2f(0, .15*sin((180 / PI) * frames))); //slowly move the menu to give a floating/breathing effect


			}

			cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

			window.clear();
			window.draw(background1);
			window.draw(background2);
			window.draw(menu);
			window.draw(cursor);
			window.display();
		}

		window.clear();

	}
void introsplash(sf::RenderWindow& window){
		window.setMouseCursorVisible(false);

		int alpha = 255;
		sf::Time targetTime = sf::seconds(1);
		sf::Clock timer;

		sf::RectangleShape block1(sf::Vector2f(1920, 1080));
		sf::RectangleShape block2(sf::Vector2f(1920, 1080));
		sf::RectangleShape block3(sf::Vector2f(1920, 1080));
		sf::Texture t1;
		sf::Texture t2;
		sf::Texture t3;

		if (!t1.loadFromFile("assets/textures/MainScreen/mainmenu_splash.png"))
		{
			std::cout << "Error loading the t1 texture in function introsplash (Lunar Launcher.cpp) " << std::endl;
		}
		if (!t2.loadFromFile("assets/textures/MainScreen/mainmenu_splash_ol1.png"))
		{
			std::cout << "Error loading the file mainmenu_splash-ol1 in function introsplash() (Lunar Launcher.cpp) " << std::endl;
		}if (!t3.loadFromFile("assets/textures/MainScreen/backgroundtexture.png"))
		{
			std::cout << "Error loading the file mainmenu_splash-ol1 in function introsplash() (Lunar Launcher.cpp) " << std::endl;
		}
		block1.setTexture(&t1);
		block2.setTexture(&t2);
		block3.setTexture(&t3);
	
		for (float alpha1 = 1; alpha1 < 255; alpha1 = alpha1 + 0.8)
		{

			block1.setFillColor(sf::Color(255, 255, 255, alpha1));

			window.clear();
			window.draw(block1);

			window.display();
		}
		window.clear();

		for (float alpha2 = 1; alpha2 < 255; alpha2 = alpha2 + 0.3)
		{

			block2.setFillColor(sf::Color(255, 255, 255, alpha2));

			window.clear();
			window.draw(block1);
			window.draw(block2);

			window.display();
		}


		for (float alpha = 1; alpha < 255; alpha = alpha + 0.4)
		{

			block3.setFillColor(sf::Color(0, 0, 0, alpha));

			window.clear();
			window.draw(block1);
			window.draw(block2);
			window.draw(block3);

			window.display();
		}


		clearscreen(window);
		return;
	
	
	
	}
	
	int main()
{

		sf::Music music;
		musicHandler(music);
		console();
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "L U N A R  L A U N C H E R ", sf::Style::Fullscreen);
	
	if (DEBUG_GLOBAL == false) { introsplash(window); }
	window.setMouseCursorVisible(false);
	mainmenu(window, music);
	return 0;
}