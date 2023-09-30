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
	static const float PLAYER_SPEED;
	static const std::uint16_t PLAYER_JUMP_STEPS;
	GravityManager gravityManager;

	Player();
	sf::RectangleShape getShape();
	void keyboardInputHandling(float deltaTime);
	void checkBottomCollisionsAndUpdateStatus(std::shared_ptr<AGameObject> other);
	void checkBottomCollisionsAndUpdateStatus(const std::vector<std::shared_ptr<AGameObject>>& others);

	sf::FloatRect getHitbox() override;
	void update(float deltaTime) override;

private:
	sf::RectangleShape shape;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};