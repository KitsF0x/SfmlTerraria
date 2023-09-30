#include "GravityManager.hpp"

const float GravityManager::BASE_HORIZONTAL_SPEED{ 100.0f };
const std::uint16_t GravityManager::JUMP_STEP_COUNTER_INIT_VALUE{ 2000 };
const float GravityManager::BASE_VERTICAL_SPEED{ 300.0f };

GravityManager::GravityManager(sf::Transformable& transformable)
	: transformable(transformable)
{
}

void GravityManager::handleFall(float deltaTime)
{
	if (status == PlayerStatus::FALLING) {
		transformable.move(sf::Vector2f{ 0.0f, BASE_VERTICAL_SPEED * deltaTime });
	}
}

void GravityManager::handleJump(float deltaTime)
{
	if (status != PlayerStatus::ON_GROUND) {
		if (this->jumpStepCounter > 0) {
			this->jumpStepCounter--;
		}
		else
		{
			// jumpStepCounter == 0
			this->setStatus(PlayerStatus::FALLING);
		}
		if (status != PlayerStatus::FALLING) {
			transformable.move(sf::Vector2f{ 0.0f, -BASE_VERTICAL_SPEED * deltaTime });
		}
	}
}

void GravityManager::setStatus(PlayerStatus status)
{
	this->status = status;
}

PlayerStatus GravityManager::getStatus() const
{
	return status;
}

std::uint16_t GravityManager::getJumpStepCounter() const
{
	return jumpStepCounter;
}

void GravityManager::triggerJump()
{
	if (getStatus() == PlayerStatus::ON_GROUND)
	{
		this->setStatus(PlayerStatus::JUMPING);
		this->jumpStepCounter = JUMP_STEP_COUNTER_INIT_VALUE;
	}
}