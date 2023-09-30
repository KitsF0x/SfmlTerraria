#pragma once

#include <cstdint>
#include <SFML/Graphics/Transformable.hpp>
#include "GameObjectStatus.hpp"
#include "Direction.hpp"

class GravityManager
{
public:
	static const float BASE_HORIZONTAL_SPEED;
	static const float BASE_VERTICAL_SPEED;

	GravityManager(sf::Transformable& transformable);
	void handleFall(float deltaTime, float horizontalSpeed);
	void handleJump(float deltaTime, float horizontalSpeed);
	void setStatus(GameObjectStatus status);
	GameObjectStatus getStatus() const;
	std::uint16_t getJumpStepCounter() const;
	void triggerJump(std::uint16_t jumpSteps);

private:
	sf::Transformable& transformable;
	GameObjectStatus status{ GameObjectStatus::ON_GROUND };
	std::uint16_t jumpStepCounter{ 0 };
};