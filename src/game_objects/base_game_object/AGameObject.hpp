#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <memory>
#include <vector>
#include "Direction.hpp"

class AGameObject : public sf::Drawable, public sf::Transformable
{
public:
	bool collides(sf::FloatRect otherArea);
	bool collidesTop(sf::FloatRect otherArea);
	bool collidesBottom(sf::FloatRect otherArea);
	bool collidesLeft(sf::FloatRect otherArea);
	bool collidesRight(sf::FloatRect otherArea);

	void moveGameObject(Direction direction, float deltaTime, float speed);

	bool isCollidingWithOther(std::shared_ptr<AGameObject> other);
	bool isCollidingWithOther(std::shared_ptr<AGameObject> other, Direction direction);
	bool isCollidingWithOtherFromVector(const std::vector<std::shared_ptr<AGameObject>>& others);
	bool isCollidingWithOtherFromVector(const std::vector<std::shared_ptr<AGameObject>>& others, Direction direction);

	virtual sf::FloatRect getHitbox() = 0;
	virtual void update(float deltaTime) = 0;
	virtual ~AGameObject() = default;
};