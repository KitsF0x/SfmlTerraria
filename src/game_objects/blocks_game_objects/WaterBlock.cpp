#include "WaterBlock.hpp"

WaterBlock::WaterBlock()
{
	shape.setFillColor(sf::Color::Blue);
	shape.setSize(sf::Vector2f{ BLOCK_SIZE, BLOCK_SIZE });
}

sf::FloatRect WaterBlock::getHitbox()
{
	return shape.getGlobalBounds();
}

void WaterBlock::update(float deltaTime)
{
	if (getPosition() != shape.getPosition())
	{
		shape.setPosition(getPosition());
	}
}

void WaterBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}