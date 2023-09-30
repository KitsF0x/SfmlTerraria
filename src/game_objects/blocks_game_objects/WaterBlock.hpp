#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include "AGameObject.hpp"
#include "BaseBlock.hpp"

class WaterBlock : public BaseBlock
{
public:
	WaterBlock();
	sf::FloatRect getHitbox() override;
	void update(float deltaTime) override;

private:
	sf::RectangleShape shape;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};