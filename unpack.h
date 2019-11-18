#pragma once
#include <SFML/Graphics.hpp>
#include <string>
int currentStars(int level);
void loadfromfile(int level, std::vector<sf::Sprite> &asteroid, std::vector<sf::Sprite> &star, std::vector<int> &star_state, std::vector<sf::CircleShape> &massive, sf::Sprite &astronaut, sf::CircleShape &blackhole, int &mass, std::string &pre_message, std::string &astronaut_message);