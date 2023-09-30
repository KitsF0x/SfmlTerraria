#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "AGameObject.hpp"
#include "BaseBlock.hpp"

class SandBlock : public BaseBlock
{
public:
	SandBlock();
	sf::FloatRect getHitbox() override;
	void update(float deltaTime) override;

private:
	sf::RectangleShape shape;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};