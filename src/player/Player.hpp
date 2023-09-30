#pragma once

#include "Direction.hpp"
#include "AGameObject.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GravityManager.hpp"
#include "GrassBlock.hpp"

class Player : public AGameObject
{
public:
	static const sf::Vector2f PLAYER_SIZE;
	static const sf::Color PLAYER_COLOR;
	GravityManager gravityManager;

	Player();
	void movePlayer(Direction direction, float deltaTime);
	void keyboardInputHandling(float deltaTime);
	sf::RectangleShape getShape();
	void detectCollisionWithBlock(GrassBlock& grassBlock);

	sf::FloatRect getHitbox() override;
	void update(float deltaTime) override;

private:
	sf::RectangleShape shape;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};