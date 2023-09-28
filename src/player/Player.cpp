#include "Player.hpp"

const sf::Vector2f Player::PLAYER_SIZE{ 10.0f, 10.0f };
const sf::Color Player::PLAYER_COLOR{ sf::Color::Blue };
const float Player::PLAYER_BASE_SPEED{ 10.0f };

Player::Player()
{
	shape.setFillColor(Player::PLAYER_COLOR);
	shape.setSize(Player::PLAYER_SIZE);
}

void Player::movePlayer(Direction direction, float deltaTime)
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
	toMove.x *= deltaTime;
	toMove.y *= deltaTime;
	this->move(toMove);
}

void Player::keyboardInputHandling(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movePlayer(Direction::NORTH, deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movePlayer(Direction::EAST, deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movePlayer(Direction::SOUTH, deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movePlayer(Direction::WEST, deltaTime);
	}
}

sf::RectangleShape Player::getShape()
{
	return shape;
}

void Player::fall(float deltaTime)
{
	movePlayer(Direction::SOUTH, deltaTime);
}

void Player::update(float deltaTime)
{
	keyboardInputHandling(deltaTime);
	shape.setPosition(getPosition());
	fall(deltaTime);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}