#include "Player.hpp"

const sf::Vector2f Player::PLAYER_SIZE{ 10.0f, 10.0f };
const sf::Color Player::PLAYER_COLOR{ sf::Color::Blue };
const float Player::PLAYER_BASE_SPEED{ 10.0f };

Player::Player()
{
	this->setFillColor(Player::PLAYER_COLOR);
	this->setSize(Player::PLAYER_SIZE);
}

void Player::movePlayer(Direction direction)
{
	sf::Vector2f toMove{ 0.0f, 0.0f };
	switch (direction)
	{
	case Direction::NORTH:
		toMove.y = -PLAYER_BASE_SPEED;
		break;
	case Direction::SOUTH:
		toMove.y = PLAYER_BASE_SPEED;
		break;
	case Direction::EAST:
		toMove.x = PLAYER_BASE_SPEED;
		break;
	case Direction::WEST:
		toMove.x = -PLAYER_BASE_SPEED;
		break;
	}
	this->move(toMove);
}

void Player::keyboardInputHandling()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movePlayer(Direction::NORTH);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movePlayer(Direction::EAST);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movePlayer(Direction::SOUTH);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movePlayer(Direction::WEST);
	}
}