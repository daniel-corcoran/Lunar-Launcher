#pragma once
#include <SFML/Graphics.hpp>
bool iswithin(sf::Vector2i mousepos, sf::Vector2f UL, sf::Vector2f BR);
void loading(sf::RenderWindow &window); 
bool exit(sf::RenderWindow &window, sf::Texture &bg);
	