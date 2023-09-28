#include "Player.hpp"

const sf::Vector2f Player::PLAYER_SIZE{ 10.0f, 10.0f };
const sf::Color Player::PLAYER_COLOR{ sf::Color::Blue };
const float Player::PLAYER_BASE_SPEED{ 10.0f };
const std::uint16_t Player::JUMP_STEP_COUNTER_INIT_VALUE{ 500 };

Player::Player()
{
	shape.setFillColor(Player::PLAYER_COLOR);
	shape.setSize(Player::PLAYER_SIZE);
}

void Player::movePlayer(Direction direction, float deltaTime)
{
	sf::Vector2f toMove{ 0.0f, 0.0f };
	switch (direction)
	{
	case Direction::NORTH:
		toMove.y = -PLAYER_BASE_SPEED;
		break;
	case Direction::SOUTH:
		toMove.y = PLAYER_BASE_SPEED;
		break;
	case Direction::EAST:
		toMove.x = PLAYER_BASE_SPEED;
		break;
	case Direction::WEST:
		toMove.x = -PLAYER_BASE_SPEED;
		break;
	}
	toMove.x *= deltaTime;
	toMove.y *= deltaTime;
	this->move(toMove);
}

void Player::keyboardInputHandling(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		movePlayer(Direction::NORTH, deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		movePlayer(Direction::EAST, deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		movePlayer(Direction::SOUTH, deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		movePlayer(Direction::WEST, deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		triggerJump();
	}
}

sf::RectangleShape Player::getShape()
{
	return shape;
}

void Player::handleFall(float deltaTime)
{
	if (status == PlayerStatus::FALLING) {
		movePlayer(Direction::SOUTH, deltaTime);
	}
}

void Player::handleJump(float deltaTime)
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
			movePlayer(Direction::NORTH, deltaTime);
		}
	}
}

void Player::setStatus(PlayerStatus status)
{
	this->status = status;
}

PlayerStatus Player::getStatus() const
{
	return status;
}

void Player::update(float deltaTime)
{
	keyboardInputHandling(deltaTime);
	shape.setPosition(getPosition());
	handleJump(deltaTime);
	handleFall(deltaTime);
	std::cout << jumpStepCounter << " " << getPosition().y << " ";
	if (status == PlayerStatus::ON_GROUND) {
		std::cout << "ON_GROUND" << std::endl;
	}
	if (status == PlayerStatus::FALLING) {
		std::cout << "FALLING" << std::endl;
	}
	if (status == PlayerStatus::JUMPING) {
		std::cout << "JUMPING" << std::endl;
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}

std::uint16_t Player::getJumpStepCounter() const
{
	return jumpStepCounter;
}

void Player::triggerJump()
{
	if (getStatus() == PlayerStatus::ON_GROUND)
	{
		this->setStatus(PlayerStatus::JUMPING);
		this->jumpStepCounter = Player::JUMP_STEP_COUNTER_INIT_VALUE;
	}
}