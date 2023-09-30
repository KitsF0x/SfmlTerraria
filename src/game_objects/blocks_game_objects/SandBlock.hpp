#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "AGameObject.hpp"

class SandBlock : public AGameObject
{
public:
	static const float BLOCK_SIZE;

	SandBlock();
	sf::FloatRect getHitbox() override;
	void update(float deltaTime) override;

private:
	sf::RectangleShape shape;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};