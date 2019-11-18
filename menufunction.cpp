#include "pch.h"
#include <SFML/Graphics.hpp>
bool iswithin(sf::Vector2i mousepos, sf::Vector2f UL, sf::Vector2f BR) {
	if ((mousepos.x >= UL.x) && (mousepos.x <= BR.x) && (mousepos.y >= UL.y)&& (mousepos.y <= BR.y)){
		return true;
	}
	return false;
}
void loading(sf::RenderWindow &window) {
	sf::RectangleShape loaderbox(sf::Vector2f(548, 206));
	sf::Texture texture;
	texture.loadFromFile("assets/textures/sprites/loading.png");
	loaderbox.setTexture(&texture);
	loaderbox.setPosition(sf::Vector2f(1980 / 2 - 274, 850));
	window.draw(loaderbox);
	window.display();
	
}
bool exit(sf::RenderWindow &window, sf::Texture &bg) {
	//are you sure you want to exit? 
	return true;

	//FIXME


}
