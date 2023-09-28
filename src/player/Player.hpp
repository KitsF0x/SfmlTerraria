#pragma once

#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "IGameObject.hpp"
#include "PlayerStatus.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

class Player : public IGameObject
{
public:
	static const sf::Vector2f PLAYER_SIZE;
	static const sf::Color PLAYER_COLOR;
	static const float PLAYER_BASE_HORIZONTAL_SPEED;
	static const std::uint16_t JUMP_STEP_COUNTER_INIT_VALUE;
	static const float PLAYER_BASE_VERTICAL_SPEED;

	Player();
	void movePlayer(Direction direction, float deltaTime);
	void keyboardInputHandling(float deltaTime);
	sf::RectangleShape getShape();
	void handleFall(float deltaTime);
	void handleJump(float deltaTime);
	void setStatus(PlayerStatus status);
	PlayerStatus getStatus() const;
	std::uint16_t getJumpStepCounter() const;
	void triggerJump();

	void update(float deltaTime) override;

private:
	sf::RectangleShape shape;
	PlayerStatus status{ PlayerStatus::ON_GROUND };
	std::uint16_t jumpStepCounter{ 0 };

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};