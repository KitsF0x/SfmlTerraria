#pragma once

#include <SFML/Graphics.hpp>
#include "Direction.hpp"

class Player : public sf::RectangleShape
{
public:
	static const sf::Vector2f PLAYER_SIZE;
	static const sf::Color PLAYER_COLOR;
	static const float PLAYER_BASE_SPEED;

	Player();
	void movePlayer(Direction direction);
	void keyboardInputHandling();
};