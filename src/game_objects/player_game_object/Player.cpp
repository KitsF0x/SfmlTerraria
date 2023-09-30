#include "Player.hpp"

const sf::Vector2f Player::PLAYER_SIZE{ 10.0f, 10.0f };
const sf::Color Player::PLAYER_COLOR{ sf::Color::Blue };

Player::Player() : gravityManager(*this)
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
		// Jump
		toMove.y = -gravityManager.BASE_VERTICAL_SPEED;
		break;
	case Direction::SOUTH:
		toMove.y = gravityManager.BASE_VERTICAL_SPEED;
		break;
	case Direction::EAST:
		toMove.x = gravityManager.BASE_HORIZONTAL_SPEED;
		break;
	case Direction::WEST:
		toMove.x = -gravityManager.BASE_HORIZONTAL_SPEED;
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
		gravityManager.triggerJump();
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
	gravityManager.handleJump(deltaTime);
	gravityManager.handleFall(deltaTime);
}

sf::FloatRect Player::getHitbox()
{
	return shape.getGlobalBounds();
}

void Player::detectCollisionWithBlock(GrassBlock& grassBlock)
{
	bool ok = collidesBottom(grassBlock.getHitbox());
	if (ok && gravityManager.getStatus() == GameObjectStatus::FALLING)
	{
		gravityManager.setStatus(GameObjectStatus::ON_GROUND);
	}
}

void Player::detectStandingOnAnyBlockFromVector(const std::vector<GrassBlock>& blocks)
{
	auto pos = std::find_if(blocks.begin(), blocks.end(), [this](GrassBlock block) {
		return this->collidesBottom(block.getHitbox());
		});
	if (pos != blocks.end()) {
		gravityManager.setStatus(GameObjectStatus::ON_GROUND);
	}
	else
	{
		gravityManager.setStatus(GameObjectStatus::FALLING);
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}