#pragma once

#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "IGameObject.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include "GravityManager.hpp"

class Player : public IGameObject
{
public:
	static const sf::Vector2f PLAYER_SIZE;
	static const sf::Color PLAYER_COLOR;
	GravityManager gravityManager;

	Player();
	void movePlayer(Direction direction, float deltaTime);
	void keyboardInputHandling(float deltaTime);
	sf::RectangleShape getShape();
	bool collidesTop(sf::FloatRect otherArea);
	bool collidesBottom(sf::FloatRect otherArea);
	bool collidesLeft(sf::FloatRect otherArea);
	bool collidesRight(sf::FloatRect otherArea);

	void update(float deltaTime) override;

private:
	sf::RectangleShape shape;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};