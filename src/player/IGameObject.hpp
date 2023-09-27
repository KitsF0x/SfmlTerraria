#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class IGameObject : public sf::Drawable, public sf::Transformable
{
public:
	virtual void update(float deltaTime) = 0;
	virtual ~IGameObject() = default;
};