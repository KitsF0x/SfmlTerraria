#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Rect.hpp>

class AGameObject : public sf::Drawable, public sf::Transformable
{
public:
	bool collides(sf::FloatRect otherArea);
	bool collidesTop(sf::FloatRect otherArea);
	bool collidesBottom(sf::FloatRect otherArea);
	bool collidesLeft(sf::FloatRect otherArea);
	bool collidesRight(sf::FloatRect otherArea);

	virtual sf::FloatRect getHitbox() = 0;
	virtual void update(float deltaTime) = 0;
	virtual ~AGameObject() = default;
};