#include "GravityManager.hpp"

const float GravityManager::BASE_HORIZONTAL_SPEED{ 100.0f };
const float GravityManager::BASE_VERTICAL_SPEED{ 300.0f };

GravityManager::GravityManager(sf::Transformable& transformable)
	: transformable(transformable)
{
}

void GravityManager::handleFall(float deltaTime, float horizontalSpeed)
{
	if (status == GameObjectStatus::FALLING) {
		transformable.move(sf::Vector2f{ 0.0f, horizontalSpeed * deltaTime });
	}
}

void GravityManager::handleJump(float deltaTime, float horizontalSpeed)
{
	if (status != GameObjectStatus::ON_GROUND) {
		if (this->jumpStepCounter > 0) {
			this->jumpStepCounter--;
		}
		else
		{
			// jumpStepCounter == 0
			this->setStatus(GameObjectStatus::FALLING);
		}
		if (status != GameObjectStatus::FALLING) {
			transformable.move(sf::Vector2f{ 0.0f, -horizontalSpeed * deltaTime });
		}
	}
}

void GravityManager::setStatus(GameObjectStatus status)
{
	this->status = status;
}

GameObjectStatus GravityManager::getStatus() const
{
	return status;
}

std::uint16_t GravityManager::getJumpStepCounter() const
{
	return jumpStepCounter;
}

void GravityManager::triggerJump(std::uint16_t jumpSteps)
{
	if (getStatus() == GameObjectStatus::ON_GROUND)
	{
		this->setStatus(GameObjectStatus::JUMPING);
		this->jumpStepCounter = jumpSteps;
	}
}