// q|DANIEL-_-CORCORAN|p
//This code was written by Daniel P. Corcoran. Please do not copy
//Or modify this code in any way, for any reason. 



//#include "pch.h"
//this file takes the input from unpack and runs the game, then outputs the data to the progress file
#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h> /*printf, scanf, puts, NULL*/
#include <cmath>
#include <time.h> /*time*/
#include <stdlib.h> /*srand, rand*/
#include <cstdlib>

//Program-dependent functions
#include "unpack.h"
#include "savedata.h"
#include "process.h"
#include "menufunction.h"
#include "Lunar Launcher.h"
#define pi 3.14159; //G is a the gravitational constant
//GAME TOOLS
void sfx(int number) {
	sf::Sound sound;
	sf::SoundBuffer buffer;
	switch (number) {
	case(1):
		{
			buffer.loadFromFile("assets/sound/sfx/explosion.wav");
		}
	}

	sound.setBuffer(buffer);
	sound.play();


}
void clear_screen(sf::RenderWindow& window, sf::View view) {

	int alpha = 0;
	sf::Time targetTime = sf::seconds(1);
	sf::Clock timer;
	sf::RectangleShape clearblock(sf::Vector2f(1920, 1080)); //initialize the black screen rectangle
	clearblock.setOrigin(1920 / 2, 1080 / 2);
	clearblock.setPosition(view.getCenter());
	clearblock.setFillColor(sf::Color::Black);
	bool var = true;
	while (var)
	{
		if (alpha > 50) {
			var = false;
		}
		clearblock.setFillColor(sf::Color(0, 0, 0, alpha));
		alpha = alpha + 2;
		window.draw(clearblock);
		window.display();
	}


}
void showMessage(sf::RenderWindow &window, int level, std::string inputMessage) {
	std::cout << "SHOW ASTRONAUT MESSAGE! hooray. ";


	sf::View MenuView;
	MenuView.setSize(1920, 1080);
	MenuView.setCenter(1920 / 2, 1080 / 2);
	sf::Sprite cursor;
	sf::Texture cursorImg;
	cursorImg.loadFromFile("assets/textures/sprites/empty.png");
	cursor.setTexture(cursorImg);
	sf::Font font;
	if (!font.loadFromFile("assets/data/boldfont.ttf")) { std::cout << "Error loading font from assets/data/font.ttf\n"; }


	window.setView(MenuView);
	clear_screen(window, MenuView);
	sf::Texture messagetexture;
	sf::Texture bgtexture;
	if (!messagetexture.loadFromFile("assets/textures/sprites/message.png"))
	{
		std::cout << "Error loading the pausemenu texture in funtion pausegame() " << std::endl;
	}
	if (!bgtexture.loadFromFile("assets/textures/gamemenu_bg.png"))
	{
		std::cout << "Error loading the levelselectiontexture in funtion levelselection() " << std::endl;
	}

	sf::RectangleShape messageBox(sf::Vector2f(548, 206));
	messageBox.setTexture(&messagetexture);
	sf::RectangleShape bg(sf::Vector2f(1920, 1080));
	bg.setTexture(&bgtexture);
	messageBox.setPosition(1920 / 2 - 548 / 2, 1080 / 2 - 206 / 2);

	//GET STRING MESSAGE!
	std::string messageValue = inputMessage;
		//"\nThanks for rescuing me!\nSpace is a scary place!";



	sf::Text message;
	message.setCharacterSize(22);
	message.setString(messageValue);
	message.setFont(font);
	message.setPosition(1920 / 2 - 548 / 2 + 155, 1080 / 2 - 206 / 2 + 30);

	float frame = 0;
	float displacement = 0;
	for (int i = 0; i < 270; i++) {
		//-------Menu Loop! This will only break to reference another window. -------//

		frame = frame + 0.001; //Frame incremental for oscillating objects
		displacement = .15*sin(57.29 * frame);

		









		message.move(0, displacement);
		messageBox.move(0, displacement);
		sf::Event event;
		{
			while (window.pollEvent(event)) //Within this loop we might be able to change the 
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::MouseButtonPressed) {
					clear_screen(window, MenuView);
					return;
				}
			}
		}


				//-------Menu Loop! This will only break to reference another window. -------//




				window.setView(MenuView);

				window.clear();

				window.draw(bg);
				window.draw(messageBox);
				window.draw(message);
			//	cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
			//	window.draw(cursor);

				window.display();



			
	}
	clear_screen(window, MenuView);
}
void gameWon(sf::RenderWindow &window, int level, sf::Music &music) {
	//clear_screen(window);

	sf::Sprite cursor;
	sf::Texture cursorImg;
	cursorImg.loadFromFile("assets/textures/sprites/cursor.png");
	cursor.setTexture(cursorImg);

	if (level == getmaxlevel()) { // If the player is currently playing the highest available level, progress up one
		newmaxlevel(level); //Increase the value in the level file by 1
	}
	sf::View PlayerView;
	PlayerView.setSize(1920, 1080);

	PlayerView.setCenter(1920 / 2, 1080 / 2);
	window.setView(PlayerView);

	
clear_screen(window, PlayerView);
sf::Texture menutexture;
sf::Texture bgtexture;

if (!menutexture.loadFromFile("assets/textures/win.png"))
{
	std::cout << "Error loading the levelselectiontexture in funtion levelselection() " << std::endl;
}
if (!bgtexture.loadFromFile("assets/textures/gamemenu_bg.png"))
{
	std::cout << "Error loading the levelselectiontexture in funtion levelselection() " << std::endl;
}

sf::RectangleShape menu(sf::Vector2f(950.0, 540.0));
sf::RectangleShape bg(sf::Vector2f(1920, 1080));
bg.setTexture(&bgtexture);

menu.setTexture(&menutexture);
menu.setPosition(515.0, 200.0);


float frame = 0;
float displacement = 0;
while (true) {
	//-------Menu Loop! This will only break to reference another window. -------//

	frame = frame + 0.001; //Frame incremental for oscillating objects
	displacement = .15*sin(57.29 * frame);


	menu.move(0, displacement);
	sf::Event event;
	while (window.pollEvent(event)) //Within this loop we might be able to change the 
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::KeyPressed)
		{
			//IN GAME BUTTONS
			//ESCAPE
			//if (event.key.code == sf::Keyboard::Escape)
			//{
			//	process(level, window);
			//}

		}
		if (event.type == sf::Event::MouseButtonPressed) {

			sf::Vector2i mousepos = sf::Mouse::getPosition();
			//std::cout << "\n____________\n";
			//std::cout << "\nMouse X: " << mousepos.x;
			//std::cout << "\nMouse Y: " << mousepos.y;

			if (event.key.code == sf::Mouse::Left) {
				//Create planet
				int x = menu.getPosition().x;
				int y = menu.getPosition().y;

				if (iswithin(mousepos, sf::Vector2f(x + 343, y + 175), sf::Vector2f(x + 573, y + 229))) { //Next level
					process(level + 1, window, music);
				}
				if (iswithin(mousepos, sf::Vector2f(x + 349, y + 249), sf::Vector2f(x + 572, y + 304))) {
					//Play again
					process(level, window , music);
				}
				if (iswithin(mousepos, sf::Vector2f(x + 360, y + 321), sf::Vector2f(x + 562, y + 372))) { //Main Menu
					mainmenu(window, music);
				}
				if (iswithin(mousepos, sf::Vector2f(x + 418, y + 392), sf::Vector2f(x + 501, y + 444))) { //Main Menu
					std::exit(0); //code 0 for a successful exit!
				}
			}

		}
	}

	//-------Menu Loop! This will only break to reference another window. -------//




	window.setView(PlayerView);
	window.clear();
	window.draw(bg);
	window.draw(menu);
	cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
	window.draw(cursor);
	window.display();
}
}
void gameOver(sf::RenderWindow &window, int level, sf::Music &music) {
	
	sf::View PlayerView;
	PlayerView.setSize(1920, 1080);
	PlayerView.setCenter(1920 / 2, 1080 / 2);

	window.setView(PlayerView);
	bool waiting = true;
	clear_screen(window, PlayerView);
	sf::Texture menutexture;
	sf::Texture bgtexture;
	if (!menutexture.loadFromFile("assets/textures/game_over.png"))
	{
		std::cout << "Error loading the levelselectiontexture in funtion levelselection() " << std::endl;
	}
	if (!bgtexture.loadFromFile("assets/textures/gamemenu_bg.png"))
	{
		std::cout << "Error loading the levelselectiontexture in funtion levelselection() " << std::endl;
	}

	sf::RectangleShape menu(sf::Vector2f(950.0, 540.0));
	menu.setTexture(&menutexture);
	sf::RectangleShape bg(sf::Vector2f(1920, 1080));
	bg.setTexture(&bgtexture);
	menu.setPosition(515.0, 200.0);

	float frame = 0;
	float displacement = 0;
	while (true) {
		//-------Menu Loop! This will only break to reference another window. -------//

		frame = frame + 0.001; //Frame incremental for oscillating objects
		displacement = .15*sin(57.29 * frame);
		sf::Sprite cursor;
		sf::Texture cursorImg;
		cursorImg.loadFromFile("assets/textures/sprites/cursor.png");
		cursor.setTexture(cursorImg);


		menu.move(0, displacement);
		sf::Event event;
		while (window.pollEvent(event)) //Within this loop we might be able to change the 
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				//IN GAME BUTTONS
				//ESCAPE
				if (event.key.code == sf::Keyboard::Escape)
				{
					process(level, window, music);
				}

			}
			if (event.type == sf::Event::MouseButtonPressed) {

				sf::Vector2i mousepos = sf::Mouse::getPosition();
				//std::cout << "\n____________\n";
				//std::cout << "\nMouse X: " << mousepos.x;
				//std::cout << "\nMouse Y: " << mousepos.y;

				if (event.key.code == sf::Mouse::Left) {
					
					int x = menu.getPosition().x;
					int y = menu.getPosition().y;
					if (iswithin(mousepos, sf::Vector2f(x+383,y+ 210), sf::Vector2f(x+537,y+ 276))) { //User clocked on the "Retry" button;
						process(level, window, music);
					}
					if (iswithin(mousepos, sf::Vector2f(x+355,y+ 294), sf::Vector2f(x+565,y+ 359))) {
						//Goto main menu...
						mainmenu(window, music);
					}
					if (iswithin(mousepos, sf::Vector2f(x + 411, y + 376), sf::Vector2f(x + 510, y + 443))) {
						//FIXME: Confirmation!
						
						std::exit(0); //EXIT SUCCESS


					}

				}

			}
		}
		
			//-------Menu Loop! This will only break to reference another window. -------//




			window.setView(PlayerView);

			window.clear();

			window.draw(bg);
			window.draw(menu);
			cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
			window.draw(cursor);


			window.display();



		}

}
void pauseGame(sf::RenderWindow &window, sf::View returnView, sf::Music &music) {
	sf::View MenuView;
	MenuView.setSize(1920, 1080);
	MenuView.setCenter(1920 / 2, 1080 / 2);
	sf::Sprite cursor;
	sf::Texture cursorImg;
	cursorImg.loadFromFile("assets/textures/sprites/cursor.png");
	cursor.setTexture(cursorImg);

	window.setView(MenuView);
	bool waiting = true;
	clear_screen(window, MenuView);
	sf::Texture menutexture;
	sf::Texture bgtexture;
	if (!menutexture.loadFromFile("assets/textures/paused.png"))
	{
		std::cout << "Error loading the pausemenu texture in funtion pausegame() " << std::endl;
	}
	if (!bgtexture.loadFromFile("assets/textures/gamemenu_bg.png"))
	{
		std::cout << "Error loading the levelselectiontexture in funtion levelselection() " << std::endl;
	}

	sf::RectangleShape menu(sf::Vector2f(950.0, 540.0));
	menu.setTexture(&menutexture);
	sf::RectangleShape bg(sf::Vector2f(1920, 1080));
	bg.setTexture(&bgtexture);
	menu.setPosition(515.0, 200.0);

	float frame = 0;
	float displacement = 0;
	while (true) {
		//-------Menu Loop! This will only break to reference another window. -------//

		frame = frame + 0.001; //Frame incremental for oscillating objects
		displacement = .15*sin(57.29 * frame);


		menu.move(0, displacement);
		sf::Event event;
		while (window.pollEvent(event)) //Within this loop we might be able to change the 
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				//IN GAME BUTTONS
				//ESCAPE
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.setView(returnView);
					return;
				}

			}
			if (event.type == sf::Event::MouseButtonPressed) {

				sf::Vector2i mousepos = sf::Mouse::getPosition();
				//std::cout << "\n____________\n";
				//std::cout << "\nMouse X: " << mousepos.x;
				//std::cout << "\nMouse Y: " << mousepos.y;

				if (event.key.code == sf::Mouse::Left) {

					int x = menu.getPosition().x;
					int y = menu.getPosition().y;
					if (iswithin(mousepos, sf::Vector2f(x + 383, y + 210), sf::Vector2f(x + 537, y + 276))) { //User clocked on the "Resume
						window.setView(returnView);
						return;
					}
					if (iswithin(mousepos, sf::Vector2f(x + 355, y + 294), sf::Vector2f(x + 565, y + 359))) {
						//Goto main menu...
						mainmenu(window, music);
					}
					if (iswithin(mousepos, sf::Vector2f(x + 411, y + 376), sf::Vector2f(x + 510, y + 443))) {
						//FIXME: Confirmation!

						std::exit(0); //EXIT SUCCESS


					}

				}

			}
		}

		//-------Menu Loop! This will only break to reference another window. -------//




		window.setView(MenuView);

		window.clear();

		window.draw(bg);
		window.draw(menu);

		cursor.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
		window.draw(cursor);

		window.display();



	}
}
bool checkBlackHole(sf::Vector2f position, sf::Vector2f bposition) {
	float distance;
	float deltaX = position.x - bposition.x;
	float deltaY = position.y - bposition.y;
	distance = sqrt(pow(deltaY, 2) + pow(deltaX, 2));
	if (distance < 120) {
		return true; //Game has been won! :)
	}
	return false;
}
bool checkPlanetCollision(sf::Vector2f position, std::vector<sf::CircleShape> planets) {
	float distance;
	for (int i = 0; i < planets.size(); i++) {

		float deltaX = position.x - planets[i].getPosition().x;
		float deltaY = position.y - planets[i].getPosition().y;
		distance = sqrt(pow(deltaY, 2) + pow(deltaX, 2));

		if (distance < planets[i].getRadius()) {
			return true; //Game has been lost :(
		}
	}
	return false;




}
int checkStarCollision(sf::Vector2f position, std::vector<sf::Sprite> &asteroids, float frame) {
	//True/False
	   //Calculate the distance from the player to each asteroid. If dist < 20 (25 is r of asteroid), we return a true. Otherwise false (safe)
float d = 0.15*sin(57 * frame);
	//This is a clone of the asteroid function, so I didn't change all the variables. Just change them later. 
	int intreturn = -1;
	float distance;
	asteroids[asteroids.size() - 1].rotate(-1);
	for (int i = 0; i < asteroids.size(); i++) {
	asteroids[i].rotate(pow(-1, (i % 2))*d); //Rotate function, in case we want to 
		float deltaX = position.x - asteroids[i].getPosition().x;
		float deltaY = position.y - asteroids[i].getPosition().y;
		distance = sqrt(pow(deltaY, 2) + pow(deltaX, 2));
		if (distance < 55) {
			std::cout << i << std::endl;
			intreturn = i; //Index of the collected star
			
			return i;
		}
	}
	return intreturn; //No star code
}
bool checkAsteroidCollision(sf::Vector2f position, std::vector<sf::Sprite> &asteroids, float frame) {
 //True/False
	//Calculate the distance from the player to each asteroid. If dist < 20 (25 is r of asteroid), we return a true. Otherwise false (safe)
	float d = 0.15*sin(57*frame);

	
	float distance;
	for (int i = 0; i < asteroids.size(); i++) {
		asteroids[i].rotate(pow(-1, (i % 2))*d);
		float deltaX = position.x - asteroids[i].getPosition().x;
		float deltaY = position.y - asteroids[i].getPosition().y;
		distance = sqrt(pow(deltaY, 2) + pow(deltaX, 2));

		if (distance < 57) {
			return true; //Game has been lost :(
		}
	}
	return false;




}
void updateView(sf::View &view, float x, float y, std::vector<sf::RectangleShape> &vector, std::vector<sf::RectangleShape> &vector2) {
	view.move(x, y);
	for (int i = 0; i < 4; i++) {
		vector[i].move(sf::Vector2f(0.66*x, 0.66*y));
	}
	for (int i = 0; i < 4; i++) {
		vector2[i].move(sf::Vector2f(0.70*x, 0.70*y));
	}
}
sf::Vector2f getForce(sf::CircleShape &player, sf::CircleShape object) {
	sf::Vector2f vector;
	float deltaX = player.getPosition().x - object.getPosition().x;
	float deltaY = player.getPosition().y - object.getPosition().y;
	float radius = sqrt(pow(deltaY, 2) + pow(deltaX, 2));
	//If Delta X is negative, Force X is Positive
	//If Delta X is positive, Force X is Negative

	//If Delta Y is Positive, Force Y is Negative
	//If Delta Y is Negative, Force Y is Positive
	float m = object.getRadius();

	double theta = asin(abs(deltaY / radius)); // Theta from x-axis (only from 0 to pi/2)
	//std::cout << "theta: " << theta << std::endl;
	vector.x = 0;
	vector.y = 0; //initialization values
	float force = 4.5 * m /pow( radius, 1.5);
	//std::cout << "force: " << force << std::endl;
	if (deltaX < 0) { //This means the force is POSITIVE in the x direction
		vector.x = cos(theta) * force;
		//std::cout << "Fx+\n";
	}
	if (deltaX > 0) { //This means the force is NEGATIVE in the x direction
		vector.x = cos(theta) * (-1) * force;
		//std::cout << "Fx-\n";
	}
	if (deltaY < 0) { //This means the force is POSITIVE in the y direction (down on the plane)
		vector.y = sin(theta) * force;
		
		//std::cout << "Fy+\n";
	}
	if (deltaY > 0) { //This means the force is NEGATIVE in the y direction (up on the plane)
		vector.y = sin(theta) * (-1) * force;
		
		//std::cout << "Fy-\n";

	}

	return vector;
}
void movePlayer(sf::View &view, sf::CircleShape &player,float &vx,float &vy, std::vector<sf::CircleShape> vector, sf::CircleShape blackHole, float &forcex, float &forcey, std::vector<sf::RectangleShape> &bgvector, std::vector<sf::RectangleShape> &starVector, std::vector<sf::CircleShape> massive)
{
	float sumFx = getForce(player, blackHole).x;
	float sumFy = getForce(player, blackHole).y;
	
	
	
	
	for (int i = 0; i < vector.size(); i++) {
		sumFx = sumFx + getForce(player, vector[i]).x;
		sumFy = sumFy + getForce(player, vector[i]).y;	 
	}
	for (int i = 0; i < massive.size(); i++) {
		sumFx = sumFx + getForce(player, massive[i]).x;
		sumFy = sumFy + getForce(player, massive[i]).y;
	}


	vx = vx+sumFx;
	vy = vy+sumFy;
	//player.rotate(acos(pow(((vx * vx) + (vy * vy)), .5)/(vx*vy + 0.5)));
	updateView(view, vx, vy, bgvector, starVector);
	player.move(sf::Vector2f(vx, vy));
	forcex = sumFx;
	forcey = sumFy; 
	//std::cout << "Player X: " << player.getPosition().x << "   Player Y: " << player.getPosition().y << std::endl;

	//We will loop through all of the planets. Calculate the total force operating
	//on the player. 

}
std::vector<sf::CircleShape> rotatePlanet(std::vector<sf::CircleShape> vector) {
	if (vector.size() != 0){
		for (int i = 0; i < vector.size(); i++) {
			int radius = vector[i].getRadius(); //Static Cast Integer
			float fradius = radius;
			if ((radius == 90)||(radius == 152)) {
				vector[i].rotate(100 / fradius);
			}
			else {
				vector[i].rotate(-100 / fradius);
			}
		}

		return vector;

}
}
std::vector<sf::RectangleShape> createGameHUD(int mass_allowance, int chosen_mass, sf::View view) {
	std::vector<sf::RectangleShape> HUDVector(4); //We will add more objects in the future...
	//Index 0: HUD Template
	//Index 1: Planet Representation
	//Index 2: Mass Remaining
	sf::RectangleShape planet(sf::Vector2f(355, 300));
	sf::RectangleShape HUD(sf::Vector2f(440, 731));
	HUD.setPosition(1420+view.getCenter().x - 960, 50 + view.getCenter().y - 540);
	planet.setPosition(1420 +33 + view.getCenter().x - 960, 50 +367 + view.getCenter().y - 540);

	sf::RectangleShape xForce(sf::Vector2f(2, 1));
	sf::RectangleShape yForce(sf::Vector2f(2, 1));
	

	HUDVector[0] = HUD;
	HUDVector[1] = planet;
	HUDVector[2] = xForce;
	HUDVector[3] = yForce;


	return HUDVector;
}
std::vector<sf::RectangleShape> updateHUD(sf::View view, std::vector<sf::RectangleShape> vector, int mass_allowance, int chosen_mass, float displacement, sf::Vector2f force) {
//FIXME: Also display the FORCES acting on the player...	
	
	
	vector[0].setPosition(sf::Vector2f(1420 + view.getCenter().x - 960, 50 + view.getCenter().y - 540 + displacement));
	vector[1].setPosition(sf::Vector2f(1420 + 33 + view.getCenter().x - 960, 50 + 367 + view.getCenter().y - 540 + displacement));
	float xmagnitude = 100 * (force.x / 0.30);
	float ymagnitude = 70 * (force.y / 0.30);
	vector[2].setPosition(sf::Vector2f(1420 + 271 + view.getCenter().x - 960, 50 + 167 + view.getCenter().y - 540 + displacement));
	vector[3].setPosition(sf::Vector2f(1420 + 271 + view.getCenter().x - 960, 50 + 167 + view.getCenter().y - 540 + displacement));
	vector[2].setSize(sf::Vector2f(xmagnitude, 2));
	vector[3].setSize(sf::Vector2f(2, ymagnitude));


	return vector;
}
std::vector<sf::CircleShape> destroyPlanet(std::vector<sf::CircleShape> vector, int x, int y, int &massallowance) {
//FIXME. When the user right clicks, destroy the planet, and return some mass to the mass vector!
	for (int i = 0; i < vector.size(); i++) {
		int xDistance = vector[i].getPosition().x - x;
		int yDistance = vector[i].getPosition().y - y;
		
		if ((sqrt(pow(xDistance, 2) + pow(yDistance, 2)) <= vector[i].getRadius())) {
			int r = vector[i].getRadius();
			switch(r) {
				//Player will get 1/2 of the mass back when destroying a planet. 
			case 90:
				massallowance += 50;
				break;
			case 120:
				massallowance += 100;
				break;
			case 152:
				massallowance += 150;
				break;
			case 180:
				massallowance += 200;
				break;
			}
			
			
			
			
			vector.erase(vector.begin() + i);








		}

}
	return vector;
}
std::vector<sf::CircleShape> createPlanet(std::vector<sf::CircleShape> vector, int x, int y, int mass) {
	//This takes the mass, x, y coordinates of a planet and puts that planet there. 
	//Radius = Ract * 50
	int radius; 
	switch (mass) {
		//I went ahead and calculated the radiuses of the planets. 
	case 100:
		//r = 2.88 * 50 = 144
		radius = 90;
		break;
	case 200:
		radius = 120;
		break;
	case 300:
		radius = 152;
		break;
	case 400:
		radius = 180;
	}
	sf::CircleShape planet;
	planet.setRadius(radius);
	planet.setPosition(x, y);
	planet.setOrigin(radius, radius);
	vector.push_back(planet);


	return vector;
}
std::vector<sf::Texture> getPlanetTextureVector() {
	sf::Texture texture100a;
	sf::Texture texture100b;
	sf::Texture texture100c;

	sf::Texture texture200a;
	sf::Texture texture200b;
	sf::Texture texture200c;

	sf::Texture texture300a;
	sf::Texture texture300b;
	sf::Texture texture300c;

	sf::Texture texture400a;
	sf::Texture texture400b;
	sf::Texture texture400c;

	if (!texture100a.loadFromFile("assets/textures/sprites/planet/100a.png")) {
		std::cout << "Error loading the planet100a sprite texture in function getHUDPlanetTextureVector" << std::endl;
	}
	if (!texture100b.loadFromFile("assets/textures/sprites/planet/100b.png")) {
		std::cout << "Error loading the planet100b sprite texture in function getHUDPlanetTextureVector" << std::endl;
	}
	if (!texture100c.loadFromFile("assets/textures/sprites/planet/100c.png")) {
		std::cout << "Error loading the planet100c sprite texture in function getHUDPlanetTextureVector" << std::endl;
	}

	if (!texture200a.loadFromFile("assets/textures/sprites/planet/200a.png")) {
		std::cout << "Error loading the planet200a HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}
	if (!texture200b.loadFromFile("assets/textures/sprites/planet/200b.png")) {
		std::cout << "Error loading the planet200b HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}
	if (!texture200c.loadFromFile("assets/textures/sprites/planet/200c.png")) {
		std::cout << "Error loading the planet200c HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}

	if (!texture300a.loadFromFile("assets/textures/sprites/planet/300a.png")) {
		std::cout << "Error loading the planet300a HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}
	if (!texture300b.loadFromFile("assets/textures/sprites/planet/300b.png")) {
		std::cout << "Error loading the planet300b HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}
	if (!texture300c.loadFromFile("assets/textures/sprites/planet/300c.png")) {
		std::cout << "Error loading the planet300c HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}

	if (!texture400a.loadFromFile("assets/textures/sprites/planet/400a.png")) {
		std::cout << "Error loading the planet400 HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}
	if (!texture400b.loadFromFile("assets/textures/sprites/planet/400b.png")) {
		std::cout << "Error loading the planet400 HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}
	if (!texture400c.loadFromFile("assets/textures/sprites/planet/400c.png")) {
		std::cout << "Error loading the planet400 HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}
	std::vector<sf::Texture> vector(12);
	//100 Mass texture options
	vector[0] = texture100a;
	vector[1] = texture100b;
	vector[2] = texture100c;
	
	//200 Mass texture options
	vector[3] = texture200a;
	vector[4] = texture200b;
	vector[5] = texture200c;

	//300 Mass texture options
	vector[6] = texture300a;
	vector[7] = texture300b;
	vector[8] = texture300c;

	//400 Mass texture options
	vector[9] = texture400a;
	vector[10] = texture400b;
	vector[11] = texture400c;

	return vector;
}
std::vector<sf::Texture> getHUDPlanetTextureVector() {
	sf::Texture texture100;
	sf::Texture texture200;
	sf::Texture texture300;
	sf::Texture texture400;
	if (!texture100.loadFromFile("assets/textures/HUD/100.png")) {
		std::cout << "Error loading the planet100 HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}
	if (!texture200.loadFromFile("assets/textures/HUD/200.png")) {
		std::cout << "Error loading the planet200 HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}
	if (!texture300.loadFromFile("assets/textures/HUD/300.png")) {
		std::cout << "Error loading the planet300 HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}
	if (!texture400.loadFromFile("assets/textures/HUD/400.png")) {
		std::cout << "Error loading the planet400 HUD texture in function getHUDPlanetTextureVector" << std::endl;
	}
	std::vector<sf::Texture> vector(4);
	vector[0] = texture100;
	vector[1] = texture200;
	vector[2] = texture300;
	vector[3] = texture400;
	return vector;
		 


}
std::vector <sf::RectangleShape> repositionBackgroundVector(sf::View view, std::vector<sf::RectangleShape> vector) {
	//This function makes sure backgrounds are seamless no matter where the camera is
	//Here's the math behind it. 
	//Any background that is not in view needs to be repositioned. 
	//How do we decide which background is in view? 
	//negative x transformation
	if (view.getCenter().x - vector[1].getPosition().x < 960) {
		//std::cout << "Trigger {1}" << std::endl;
		vector[1].move(-1920 - 1920, 0);
		vector[3].move(-1920 - 1920, 0);

	}
	if (view.getCenter().x - vector[0].getPosition().x < 960) {
		//std::cout << "Trigger {0}" << std::endl;
		vector[0].move(-1920 - 1920, 0);
		vector[2].move(-1920 - 1920, 0);
	}
	//Positive x transformations
	if (view.getCenter().x - vector[1].getPosition().x > 960+1920) {
		//std::cout << "Trigger {1}" << std::endl;
		vector[1].move(1920+1920, 0);
		vector[3].move(1920 + 1920, 0);

	}
	if (view.getCenter().x - vector[0].getPosition().x > 960+1920) {
		//std::cout << "Trigger {0}" << std::endl;
		vector[0].move(1920+1920, 0);
		vector[2].move(1920 + 1920, 0);
	}
	//Negative y transformations
	if (view.getCenter().y - vector[2].getPosition().y < 540) {
		//std::cout << "Trigger {2}\n";
		vector[2].move(0, -1080 - 1080);
		vector[3].move(0, -1080 - 1080);
	}
	if (view.getCenter().y - vector[0].getPosition().y < 540 ) {
		//std::cout << "Trigger {2}\n";
		vector[0].move(0, -1080 - 1080);
		vector[1].move(0, -1080 - 1080);
	}
	//Positive y transformations
	if (view.getCenter().y - vector[2].getPosition().y > 540+1080) {
		//std::cout << "Trigger {2}\n";
		vector[2].move(0,1080 + 1080);
		vector[3].move(0,1080 + 1080);
	}
	if (view.getCenter().y - vector[0].getPosition().y >540+1080) {
		//std::cout << "Trigger {2}\n";
		vector[0].move(0, 1080 + 1080);
		vector[1].move(0, 1080 + 1080);
	}
	return vector;

}
std::vector <sf::RectangleShape> repositionStarVector(sf::View view, std::vector<sf::RectangleShape> vector) {
	//This function makes sure backgrounds are seamless no matter where the camera is
	//Here's the math behind it. 
	//Any background that is not in view needs to be repositioned. 
	//How do we decide which background is in view? 
	//negative x transformation
	if (view.getCenter().x - vector[1].getPosition().x < 960) {
		//std::cout << "Trigger {1}" << std::endl;
		vector[1].move(-1920 - 1920, 0);
		vector[3].move(-1920 - 1920, 0);

	}
	if (view.getCenter().x - vector[0].getPosition().x < 960) {
		//std::cout << "Trigger {0}" << std::endl;
		vector[0].move(-1920 - 1920, 0);
		vector[2].move(-1920 - 1920, 0);
	}
	//Positive x transformations
	if (view.getCenter().x - vector[1].getPosition().x > 960 + 1920) {
		//std::cout << "Trigger {1}" << std::endl;
		vector[1].move(1920 + 1920, 0);
		vector[3].move(1920 + 1920, 0);

	}
	if (view.getCenter().x - vector[0].getPosition().x > 960 + 1920) {
		//std::cout << "Trigger {0}" << std::endl;
		vector[0].move(1920 + 1920, 0);
		vector[2].move(1920 + 1920, 0);
	}
	//Negative y transformations
	if (view.getCenter().y - vector[2].getPosition().y < 540) {
		//std::cout << "Trigger {2}\n";
		vector[2].move(0, -1080 - 1080);
		vector[3].move(0, -1080 - 1080);
	}
	if (view.getCenter().y - vector[0].getPosition().y < 540) {
		//std::cout << "Trigger {2}\n";
		vector[0].move(0, -1080 - 1080);
		vector[1].move(0, -1080 - 1080);
	}
	//Positive y transformations
	if (view.getCenter().y - vector[2].getPosition().y > 540 + 1080) {
		//std::cout << "Trigger {2}\n";
		vector[2].move(0, 1080 + 1080);
		vector[3].move(0, 1080 + 1080);
	}
	if (view.getCenter().y - vector[0].getPosition().y > 540 + 1080) {
		//std::cout << "Trigger {2}\n";
		vector[0].move(0, 1080 + 1080);
		vector[1].move(0, 1080 + 1080);
	}
	return vector;

}
std::vector<sf::Sprite> getObjects(int level) {//This function references the unpack function, and gets a list of objects to print to the screen
	std::vector<sf::Sprite> objects;

	return objects;
}
	/*background vector tools*/
sf::Texture getBackgroundTexture(int level) {
	char filepath[45];
	sprintf_s(filepath, "assets/textures/backgrounds/level_%d.png", level);
	std::string bg_filepath = std::string(filepath); //Convert char to str

	sf::Texture BackgroundTexture;
	if (!BackgroundTexture.loadFromFile(bg_filepath)) {
		std::cout << "Error loading the level background texture in function getBackgroundTexture in file Process.cpp" << std::endl;
	}
	else {
		std::cout << "Background File loaded successfully\n";
	}


	return BackgroundTexture;

}
sf::RectangleShape getBackground(int level) {
	sf::RectangleShape BackgroundObject(sf::Vector2f(1920, 1080));
	return BackgroundObject;
}
std::vector<sf::RectangleShape> getBackgroundVector(int level) {
	std::vector<sf::RectangleShape> vector(4);
	//Let's generate 4 background objects
	sf::RectangleShape background1 = getBackground(level);
	sf::RectangleShape background2 = getBackground(level);
	sf::RectangleShape background3 = getBackground(level);
	sf::RectangleShape background4 = getBackground(level);
	sf::Texture BackgroundTexture = getBackgroundTexture(level);
	background1.setTexture(&BackgroundTexture);
	background2.setTexture(&BackgroundTexture);
	background3.setTexture(&BackgroundTexture);
	background4.setTexture(&BackgroundTexture);
	background1.setPosition(0, 0);
	background2.setPosition(1920, 0);
	background3.setPosition(0, 1080);
	background4.setPosition(1920, 1080);

	//Set backgrounds into the vector
	vector[0] = background1;
	vector[1] = background2;
	vector[2] = background3;
	vector[3] = background4;

	//return the vector
	return vector;
}
std::vector<sf::RectangleShape> getStarVector(int level) {
	std::vector<sf::RectangleShape> vector(4);
	//Let's generate 4 background objects
	sf::RectangleShape background1 = getBackground(level);
	sf::RectangleShape background2 = getBackground(level);
	sf::RectangleShape background3 = getBackground(level);
	sf::RectangleShape background4 = getBackground(level);
	background1.setPosition(0, 0);
	background2.setPosition(1920, 0);
	background3.setPosition(0, 1080);
	background4.setPosition(1920, 1080);

	//Set backgrounds into the vector
	vector[0] = background1;
	vector[1] = background2;
	vector[2] = background3;
	vector[3] = background4;

	//return the vector
	return vector;
}
//VECTOR DRAWING TOOLS
void drawObjectVector(sf::RenderWindow& window, std::vector<sf::RectangleShape> vector) {
	//This important function draws a vector of rectangleshapes to the window, and returns the window to the function.
	
	for (int i = 0; i < vector.size(); i++) {
		window.draw(vector[i]);
	}
	}
void drawCircleVector(sf::RenderWindow& window, std::vector<sf::CircleShape> vector) {
	//This important function draws a vector of rectangleshapes to the window, and returns the window to the function.

	for (int i = 0; i < vector.size(); i++) {
		window.draw(vector[i]);
	}
}
void drawSpriteVector(sf::RenderWindow& window, std::vector<sf::Sprite> vector) {
	//This important function draws a vector of rectangleshapes to the window, and returns the window to the function.

	for (int i = 0; i < vector.size(); i++) {
		window.draw(vector[i]);
	}
}
void process(int level, sf::RenderWindow& window, sf::Music& music) {
	bool astronautBool = false; // True when we get the astronaut
	
	loading(window);
	//---Init mouse cursor--//
	sf::Sprite cursor;
	sf::Texture cursorImg;
	cursorImg.loadFromFile("assets/textures/sprites/cursor.png");
	cursor.setTexture(cursorImg);

	sf::Texture astronauttexture; 
	astronauttexture.loadFromFile("assets/textures/sprites/astronaut_sprite.png");
	sf::IntRect astronautRectangle(0, 0, 60, 60);
	sf::Sprite astronaut(astronauttexture, astronautRectangle);
	astronaut.setOrigin(30, 30);
	
	//Oscillate the sprite every 0.73 seconds? (40 frames);
	//Append the astronaut to the LAST element in game star sprite vector.

	srand(time(NULL)); //Random seed!
	
	float forcex, forcey; //These are outputted in the form of bars on the graph. 
	float VelocityX = 0;
	float VelocityY = 0;
	sf::Font font;
	if (!font.loadFromFile("assets/data/boldfont.ttf")) { std::cout << "Error loading font from assets/data/font.ttf\n"; }
	
	//Declare all game objects before unpacking
	sf::CircleShape blackHole; blackHole.setRadius(125);



	int createMass = 100;
	//---------Consolidating all game unpack functions-------
	int massBank;
	std::vector<sf::Sprite> asteroidVector;
	std::vector<sf::Sprite> gameStarVector;
	std::vector<sf::CircleShape> massiveVector;
	std::vector<int> gameStarState;
	sf::Vector2f playerPosition;
	sf::Vector2f blackHolePosition;
	std::string pre_message, astronaut_message;


	sf::Texture blackHoleTexture;
	if (!blackHoleTexture.loadFromFile("assets/textures/sprites/blackhole.png")) {
		std::cout << "Error loading the black hole texture in function process()" << std::endl;
	}
	blackHole.setOrigin(125, 125);
	blackHole.setTexture(&blackHoleTexture);



	loadfromfile(level, asteroidVector, gameStarVector, gameStarState, massiveVector, astronaut, blackHole, massBank, pre_message, astronaut_message);




	sf::View PlayerView;
	
	PlayerView.setSize(sf::Vector2f(1920, 1080));
	window.setView(PlayerView);
	int currentStarTotal = currentStars(level);
	//HUD texture
	std::vector<sf::RectangleShape> gameHUD = createGameHUD(massBank, createMass, PlayerView); 


	std::vector<sf::RectangleShape> backgroundVector = getBackgroundVector(level);
	std::vector<sf::RectangleShape> starVector = getStarVector(level);
	std::vector<sf::CircleShape> planetVector;
	
	sf::Texture AsteroidTexture;
	sf::Texture AsteroidTexture1;
	if (!AsteroidTexture.loadFromFile("assets/textures/sprites/asteroid.png")) { std::cout << "Error loading the asteroid texture in function process in file Process.cpp" << std::endl; }
	if (!AsteroidTexture1.loadFromFile("assets/textures/sprites/asteroid1.png")) { std::cout << "Error loading the asteroid texture in function process in file Process.cpp" << std::endl; }

	sf::Texture MassiveTexture;
	if (!MassiveTexture.loadFromFile("assets/textures/sprites/massive.png")) { std::cout << "Error loading the massive texture in function process in process.cpp" << std::endl; }
	
	for (int i = 0; i < asteroidVector.size(); i++) {
		if (rand() % 2 == 1) {
			asteroidVector[i].setTexture(AsteroidTexture);
		}
		else {
			asteroidVector[i].setTexture(AsteroidTexture1);

		}
	}
	for (int i = 0; i < massiveVector.size(); i++) {
		massiveVector[i].setTexture(&MassiveTexture);
	}

	sf::Texture star1;
	sf::Texture star0;
	sf::Texture empty;
	if (!star1.loadFromFile("assets/textures/sprites/star_1.png")) { std::cout << "Error loading the star_1 texture in function process in file Process.cpp" << std::endl; }
	if (!star0.loadFromFile("assets/textures/sprites/star_0.png")) { std::cout << "Error loading the star_0 texture in function process in file Process.cpp" << std::endl; }
	if (!empty.loadFromFile("assets/textures/sprites/empty.png")) { std::cout << "Error loading the --empty-- texture in function process in file Process.cpp" << std::endl; }

	
	for (int i = 0; i < gameStarVector.size(); i++) {
		switch (gameStarState[i]) {
		case 0:
			gameStarVector[i].setTexture(star0);
				break;
		case 1:
			gameStarVector[i].setTexture(star1);
			break;
		}
	}
	int totalAchievableStars = gameStarVector.size();
	gameStarVector.push_back(astronaut); //Add the astronaut to the last element in the star vector. 
	gameStarState.push_back(0); //Do we show the last astronaut?
	int AstronautIndex = gameStarVector.size()-1; //What index is the astronaut at in the star vector?

sf::Texture BackgroundTexture = getBackgroundTexture(level);
sf::Texture starTexture; if (!starTexture.loadFromFile("assets/textures/backgrounds/parallax_stars.png")) { std::cout << "Error loading the parallax star texture in function process in file Process.cpp" << std::endl; }

sf::Texture HUDTexture;	if (!HUDTexture.loadFromFile("assets/textures/HUD.png")) { std::cout << "Error loading the HUD texture in function process in file Process.cpp" << std::endl; }
std::vector<sf::Texture> planetTextureVector = getPlanetTextureVector();
std::vector<sf::Texture> HUDPlanetVector = getHUDPlanetTextureVector();




//Player object initialization
sf::CircleShape player; player.setRadius(50);
sf::Texture playerTexture;
if (!playerTexture.loadFromFile("assets/textures/sprites/player.png")) {
	std::cout << "Error loading the player texture in function process()" << std::endl;
}
player.setOrigin(50, 50);
player.setTexture(&playerTexture);
player.setPosition(0, 0);
PlayerView.setCenter(0, 0);
PlayerView.move(300, 0);



for (int i = 0; i < 4; i++) { backgroundVector[i].setTexture(&BackgroundTexture); } //Since we can't declare the object textures in another file, we do it in this loop
for (int i = 0; i < 4; i++) { starVector[i].setTexture(&starTexture); } //Since we can't declare the object textures in another file, we do it in this loop


gameHUD[0].setTexture(&HUDTexture);
bool playing = true;
gameHUD[1].setTexture(&HUDPlanetVector[0]);

sf::Text masstext;

masstext.setString(std::to_string(massBank));
masstext.setFont(font);
masstext.setFillColor(sf::Color::White);
masstext.setCharacterSize(45);



float frame = 0; //Frame for hovering the menu
float displacement = 0;
int star_index = 0;
//  |--------------------------------------------MAIN GAME LOOP----------------------------------------------------------|
frame = frame + 0.001; //Frame incremental for oscillating objects
musicHandler(music);

masstext.setString(std::to_string(massBank));

displacement = displacement + .15*sin((180 / 3.14159) * frame); //Calculate hover displacement
movePlayer(PlayerView, player, VelocityX, VelocityY, planetVector, blackHole, forcex, forcey, backgroundVector, starVector, massiveVector);
masstext.setPosition(sf::Vector2f(gameHUD[0].getPosition().x + 235, gameHUD[0].getPosition().y + 260));

//-------CHECK FOR GAME EVENTS-------///

bool fadePlayerIn = true; //Fade player in on level start
backgroundVector = repositionBackgroundVector(PlayerView, backgroundVector);//Update the background vector for the thing
starVector = repositionStarVector(PlayerView, starVector);

if (fadePlayerIn) {
	//Fade player in so people don't be fucking retarted and place planets before the game starts
	for (int f = 0; f < 255; f = f + 5) {
		player.setFillColor(sf::Color(255, 255, 255, f));
		window.setView(PlayerView);
		window.clear();
		gameHUD = updateHUD(PlayerView, gameHUD, massBank, createMass, displacement, sf::Vector2f(forcex, forcey));


		drawObjectVector(window, backgroundVector);
		drawObjectVector(window, starVector);
		drawSpriteVector(window, asteroidVector);
		drawCircleVector(window, planetVector);

		window.draw(blackHole);

		window.draw(player);

		drawObjectVector(window, gameHUD);
		blackHole.rotate(2);
		window.display();
	}
	player.setFillColor(sf::Color(255, 255, 255, 255));

}

while (playing) {
	//oscillate astronaut vector window every 40 frames...

	if ((static_cast<int>(frame * 1000) % 40 == 0) && (astronautBool == false)) {
		//Move the rectangle to the left or to the right, but alternate every 40 frames. 
		if (static_cast<int>(frame * 1000) % 80 == 0){ //Move left
		astronautRectangle.left = 0;
				  }else{

			astronautRectangle.left += 60;
		}

		}




		//  |--------------------------------------------MAIN GAME LOOP----------------------------------------------------------|
		frame = frame + 0.001; //Frame incremental for oscillating objects
		
		masstext.setString(std::to_string(massBank));

		displacement = displacement + .15*sin((180 / 3.14159) * frame); //Calculate hover displacement
		movePlayer(PlayerView, player,VelocityX,VelocityY, planetVector, blackHole, forcex, forcey, backgroundVector, starVector, massiveVector);
		masstext.setPosition(sf::Vector2f(gameHUD[0].getPosition().x + 243, gameHUD[0].getPosition().y + 257));

		//-------CHECK FOR GAME EVENTS-------///
		if (((checkAsteroidCollision(player.getPosition(), asteroidVector, frame) == true)||(checkPlanetCollision(player.getPosition(), planetVector) == true) || (checkPlanetCollision(player.getPosition(), massiveVector) == true))){
		//-------GAME OVER-----------///
			std::cout << "-------GAME OVER-------" << std::endl;
			sf::Texture death;
			death.loadFromFile("assets/textures/sprites/death.png");
			sfx(1);
			sf::IntRect deathSourceSprite(0, 0, 100, 100);
			sf::Sprite deathOverlay(death, deathSourceSprite);
			deathOverlay.setOrigin(50, 50);
			deathOverlay.setPosition(player.getPosition());
			for (int f = 0; f < 6; f++) {
				deathSourceSprite.left = 0;

				for (int g = 0; g < 6; g++) {//F is the frame
					window.setView(PlayerView);
					window.clear();

					drawObjectVector(window, backgroundVector);
					drawObjectVector(window, starVector);
					drawSpriteVector(window, asteroidVector);
					drawCircleVector(window, planetVector);
					drawCircleVector(window, massiveVector);

					window.draw(blackHole);
				
					if (f < 2) { window.draw(player); }





					window.draw(deathOverlay);



					drawObjectVector(window, gameHUD);
					blackHole.rotate(2);
					window.display();


					deathSourceSprite.left += 100;

					deathOverlay.setTextureRect(deathSourceSprite);
									   					 

				}
				deathSourceSprite.top += 100;


			}
			gameOver(window, level, music);
			return;
					   			 		  		 		}
		star_index = checkStarCollision(player.getPosition(), gameStarVector, frame);
		if (star_index != -1){ // check to see if the stars collided. -1 is the return code for "no collision" collusion lol
			if((star_index == AstronautIndex)&&(gameStarState[star_index] < 1)){//if we collected the astronaut...
				astronautBool = true; //Show string at end of game;
				std::cout << "Astronaut!! Disregard below message. \n";
			}
			
			std::cout << "Collected star " << star_index << std::endl;
			gameStarVector[star_index].setTexture(empty); //Make it transparent
			gameStarState[star_index] = 1; //Collected!
					   			 		  		  		}
		
		
		
		if (checkBlackHole(player.getPosition(), blackHole.getPosition())) {
			float dx = player.getPosition().x - blackHole.getPosition().x;
			float dy = player.getPosition().y - blackHole.getPosition().y;
//			newstars(gameStarState, level);  //Update star save data...
			for (float f = 255; f > 5; f = f - 5) {
				player.setFillColor(sf::Color(255, 255, 255, f));
				window.setView(PlayerView);
				window.clear();
				gameHUD = updateHUD(PlayerView, gameHUD, massBank, createMass, displacement, sf::Vector2f(forcex, forcey));
				player.setRadius((f / 255) * 50);
				player.move(dx / -50, dy / -50);
				
				drawObjectVector(window, backgroundVector);
				drawObjectVector(window, starVector);
				drawSpriteVector(window, asteroidVector);
				drawSpriteVector(window, gameStarVector);
				drawCircleVector(window, planetVector);

				window.draw(blackHole);

				window.draw(player);

				drawObjectVector(window, gameHUD);
				blackHole.rotate(2);
				window.display();
			}
			
			if (astronautBool) {
				showMessage(window, level, astronaut_message);

			}
			
			
			gameWon(window, level, music);}



			//Main Game Loop
			//PlayerView.rotate(5.f);
		sf::Event event;
		sf::Vector2i mousepos = sf::Mouse::getPosition(); //If the mouse is over the HUD we want to hide it. or at least make it transparent


		
		while (window.pollEvent(event)) //Within this loop we might be able to change the 
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				//IN GAME BUTTONS
				//ESCAPE
				if (event.key.code == sf::Keyboard::Escape)
				{



					pauseGame(window, PlayerView, music);
					
					for (int f = 0; f < 255; f = f + 10) { //Return by fading the player in...
						
						
						player.setFillColor(sf::Color(255, 255, 255, f));
						window.setView(PlayerView);
						window.clear();

						drawObjectVector(window, backgroundVector);
						drawObjectVector(window, starVector);
						drawSpriteVector(window, asteroidVector);
						drawSpriteVector(window, gameStarVector);
						drawCircleVector(window, massiveVector);

						drawCircleVector(window, planetVector);
						window.draw(blackHole);

						window.draw(player);

						drawObjectVector(window, gameHUD);
						blackHole.rotate(2);
						window.display();
					}
					player.setFillColor(sf::Color(255, 255, 255, 255));

				}
				if (event.key.code == sf::Keyboard::Left) {
					updateView(PlayerView, -5, 0, backgroundVector, starVector);
					
				}
				if (event.key.code == sf::Keyboard::Right) {
					updateView(PlayerView, 5, 0, backgroundVector, starVector);
				}
				if (event.key.code == sf::Keyboard::Up) {
					updateView(PlayerView, 0, -5, backgroundVector, starVector);
				}
				if (event.key.code == sf::Keyboard::Down) {
					updateView(PlayerView, 0, 5, backgroundVector, starVector);
				}
				if (event.key.code == sf::Keyboard::Num1) {
					createMass = 100;
					gameHUD[1].setTexture(&HUDPlanetVector[0]);
				}
				if (event.key.code == sf::Keyboard::Num2) {
					createMass = 200;
					gameHUD[1].setTexture(&HUDPlanetVector[1]);

				}
				if (event.key.code == sf::Keyboard::Num3) {
					createMass = 300;
					gameHUD[1].setTexture(&HUDPlanetVector[2]);

				}
				if (event.key.code == sf::Keyboard::Num4) {
					createMass = 400;
					gameHUD[1].setTexture(&HUDPlanetVector[3]);

				}
				gameHUD = updateHUD(PlayerView, gameHUD, massBank, createMass, displacement, sf::Vector2f(forcex, forcey));
				backgroundVector = repositionBackgroundVector(PlayerView, backgroundVector);
				starVector = repositionStarVector(PlayerView, starVector);
				std::cout << "Player has selected createMass of " << createMass << std::endl;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				
				mousepos = sf::Mouse::getPosition();
				//std::cout << "\n____________\n";
				//std::cout << "\nMouse X: " << mousepos.x;
				//std::cout << "\nMouse Y: " << mousepos.y;

				if (event.key.code == sf::Mouse::Left) {
					//Create planet
					//FIXME: If statement that requires sufficient MASS
					if (createMass <= massBank) {
						planetVector = createPlanet(planetVector, mousepos.x + PlayerView.getCenter().x - 960, mousepos.y + PlayerView.getCenter().y - 540, createMass);
						planetVector[planetVector.size() - 1].setTexture(&planetTextureVector[(((createMass / 100)) * 3) - rand() % 3 - 1]);
						massBank = massBank-createMass;
					}
				}
				if (event.key.code == sf::Mouse::Right) {
					planetVector = destroyPlanet(planetVector, mousepos.x + PlayerView.getCenter().x - 960, mousepos.y + PlayerView.getCenter().y - 540, massBank);


				}
				if (event.key.code == sf::Mouse::Middle) {
					//Debug by outputting the x-y coordinates of the mouse;
					std::cout << "mousex: " << cursor.getPosition().x << "\nmousey:" << cursor.getPosition().y << std::endl;
					
				}
			}
			

		}
	//-----------WINDOW DRAW SEQUENCE-------------

		//prep window
		window.setView(PlayerView);
		window.clear();
		musicHandler(music);
		//draw vectors in order of tiers
		drawObjectVector(window, backgroundVector);
		drawObjectVector(window, starVector);
		drawSpriteVector(window, asteroidVector);
		drawSpriteVector(window, gameStarVector);
		drawCircleVector(window, massiveVector);
		drawCircleVector(window, planetVector);

		window.draw(blackHole);
		window.draw(player);

		//hud draw seq
		
		drawObjectVector(window, gameHUD);
		window.draw(masstext);

		//cursor
		cursor.setPosition(mousepos.x + PlayerView.getCenter().x - 960, mousepos.y + PlayerView.getCenter().y - 540);
		window.draw(cursor);

		


		//Move game objects and prepare for next frame
		backgroundVector = repositionBackgroundVector(PlayerView, backgroundVector);
		starVector = repositionStarVector(PlayerView, starVector);
		gameHUD = updateHUD(PlayerView, gameHUD, massBank, createMass, displacement, sf::Vector2f(forcex, forcey));
		
		//Game HUD Transparency
		gameHUD[0].setFillColor(sf::Color(255, 255, 255, 255));
		gameHUD[1].setFillColor(sf::Color(255, 255, 255, 255));
		gameHUD[2].setFillColor(sf::Color(255, 0, 0, 255));
		gameHUD[3].setFillColor(sf::Color(0, 255, 0, 255));
		masstext.setFillColor(sf::Color(255, 255, 255, 255));

		//Y force magnitude




		if (mousepos.x > 1420) {
			gameHUD[0].setFillColor(sf::Color(255, 255, 255, 100));
			gameHUD[1].setFillColor(sf::Color(255, 255, 255, 100));
			gameHUD[2].setFillColor(sf::Color(255, 0, 0, 100));
			gameHUD[3].setFillColor(sf::Color(0, 255, 0, 100));
			masstext.setFillColor(sf::Color(255, 255, 255, 100));
		}

		//rotate planets and black hole
		if (planetVector.size() > 0) {
			planetVector = rotatePlanet(planetVector);
		}
		blackHole.rotate(2);
		gameStarVector[AstronautIndex].setTextureRect(astronautRectangle);
		player.rotate(VelocityX*VelocityY*0.1);
		window.display();
	
	}

























}
