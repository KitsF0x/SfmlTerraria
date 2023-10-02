#include "Player.hpp"

const sf::Vector2f Player::PLAYER_SIZE{ 20.0f, 45.0f };
const sf::Color Player::PLAYER_COLOR{ sf::Color::Blue };
const float Player::PLAYER_SPEED{ 100.0f };
const std::uint16_t Player::PLAYER_JUMP_STEPS{ 45 };

Player::Player() : gravityManager(*this)
{
	shape.setFillColor(Player::PLAYER_COLOR);
	shape.setSize(Player::PLAYER_SIZE);
}

void Player::keyboardInputHandling(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveGameObject(Direction::NORTH, deltaTime, PLAYER_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveGameObject(Direction::EAST, deltaTime, PLAYER_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveGameObject(Direction::SOUTH, deltaTime, PLAYER_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveGameObject(Direction::WEST, deltaTime, PLAYER_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		gravityManager.triggerJump(PLAYER_JUMP_STEPS);
	}
}

sf::RectangleShape Player::getShape()
{
	return shape;
}

void Player::update(float deltaTime)
{
	keyboardInputHandling(deltaTime);
	shape.setPosition(getPosition());
	gravityManager.handleJump(deltaTime, PLAYER_SPEED);
	gravityManager.handleFall(deltaTime, PLAYER_SPEED);
}

sf::FloatRect Player::getHitbox()
{
	return shape.getGlobalBounds();
}

void Player::checkBottomCollisionsAndUpdateStatus(std::shared_ptr<AGameObject> other)
{
	if (isCollidingWithOther(other, Direction::SOUTH) && gravityManager.getStatus() == GameObjectStatus::FALLING)
	{
		gravityManager.setStatus(GameObjectStatus::ON_GROUND);
	}
}
void Player::checkBottomCollisionsAndUpdateStatus(const std::vector<std::shared_ptr<AGameObject>>& others)
{
	if (isCollidingWithOtherFromVector(others, Direction::SOUTH))
	{
		gravityManager.setStatus(GameObjectStatus::ON_GROUND);
		return;
	}
	if (gravityManager.getJumpStepCounter() == 0)
	{
		gravityManager.setStatus(GameObjectStatus::FALLING);
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}