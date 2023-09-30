#include "AGameObject.hpp"

bool AGameObject::collides(sf::FloatRect otherArea)
{
	return getHitbox().intersects(otherArea);
}

bool AGameObject::collidesTop(sf::FloatRect otherArea)
{
	if (collides(otherArea))
	{
		float otherBottom = otherArea.top + otherArea.height;
		return (
			otherBottom > getHitbox().top &&
			otherBottom < getHitbox().top + getHitbox().height
			);
	}
	return false;
}

bool AGameObject::collidesBottom(sf::FloatRect otherArea)
{
	if (collides(otherArea))
	{
		float otherTop = otherArea.top;
		return (
			otherTop > getHitbox().top &&
			otherTop < getHitbox().top + getHitbox().height
			);
	}
	return false;
}

bool AGameObject::collidesLeft(sf::FloatRect otherArea)
{
	if (collides(otherArea))
	{
		float otherLeft = otherArea.left + otherArea.width;
		return (
			otherLeft > getHitbox().left &&
			otherLeft < getHitbox().left + getHitbox().width
			);
	}
	return false;
}

bool AGameObject::collidesRight(sf::FloatRect otherArea)
{
	if (collides(otherArea))
	{
		float otherLeft = otherArea.left;
		return (
			otherLeft > getHitbox().left &&
			otherLeft < getHitbox().left + getHitbox().width
			);
	}
	return false;
}

void AGameObject::moveGameObject(Direction direction, float deltaTime, float speed)
{
	sf::Vector2f toMove{ 0.0f, 0.0f };
	switch (direction)
	{
	case Direction::NORTH:
		// Jump
		toMove.y = -speed;
		break;
	case Direction::SOUTH:
		toMove.y = speed;
		break;
	case Direction::EAST:
		toMove.x = speed;
		break;
	case Direction::WEST:
		toMove.x = -speed;
		break;
	}
	toMove.x *= deltaTime;
	toMove.y *= deltaTime;
	this->move(toMove);
}

bool AGameObject::isCollidingWithOther(std::shared_ptr<AGameObject> other)
{
	return collides(other->getHitbox());
}

bool AGameObject::isCollidingWithOther(std::shared_ptr<AGameObject> other, Direction direction)
{
	switch (direction)
	{
	case Direction::NORTH:
		return collidesTop(other->getHitbox());
		break;
	case Direction::EAST:
		return collidesRight(other->getHitbox());
		break;
	case Direction::SOUTH:
		return collidesBottom(other->getHitbox());
		break;
	case Direction::WEST:
		return collidesLeft(other->getHitbox());
		break;
	}
}
bool AGameObject::isCollidingWithOtherFromVector(const std::vector<std::shared_ptr<AGameObject>>& others)
{
	bool colliding = false;
	for (auto& el : others)
	{
		if (isCollidingWithOther(el)) {
			colliding = true;
		}
	}
	return colliding;
}

bool AGameObject::isCollidingWithOtherFromVector(const std::vector<std::shared_ptr<AGameObject>>& others, Direction direction)
{
	bool colliding = false;
	for (auto& el : others)
	{
		if (isCollidingWithOther(el, direction)) {
			colliding = true;
		}
	}
	return colliding;
}