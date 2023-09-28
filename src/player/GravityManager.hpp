#pragma once

#include <cstdint>
#include <SFML/Graphics/Transformable.hpp>
#include "PlayerStatus.hpp"
#include "Direction.hpp"

class GravityManager
{
public:
	static const float BASE_HORIZONTAL_SPEED;
	static const std::uint16_t JUMP_STEP_COUNTER_INIT_VALUE;
	static const float BASE_VERTICAL_SPEED;

	GravityManager(sf::Transformable& transformable);
	void handleFall(float deltaTime);
	void handleJump(float deltaTime);
	void setStatus(PlayerStatus status);
	PlayerStatus getStatus() const;
	std::uint16_t getJumpStepCounter() const;
	void triggerJump();

private:
	sf::Transformable& transformable;
	PlayerStatus status{ PlayerStatus::ON_GROUND };
	std::uint16_t jumpStepCounter{ 0 };
};