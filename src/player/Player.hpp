#pragma once

#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "IGameObject.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

class Player : public IGameObject
{
public:
	static const sf::Vector2f PLAYER_SIZE;
	static const sf::Color PLAYER_COLOR;
	static const float PLAYER_BASE_SPEED;

	Player();
	void movePlayer(Direction direction, float deltaTime);
	void keyboardInputHandling(float deltaTime);
	sf::RectangleShape getShape();

	void update(float deltaTime) override;

private:
	sf::RectangleShape shape;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};