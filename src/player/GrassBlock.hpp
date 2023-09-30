#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "AGameObject.hpp"

class GrassBlock : public AGameObject
{
public:
	static const float BLOCK_SIZE;

	GrassBlock();
	sf::FloatRect getHitbox() override;
	void update(float deltaTime) override;

private:
	sf::RectangleShape dirtPart;
	sf::RectangleShape grassPart;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};