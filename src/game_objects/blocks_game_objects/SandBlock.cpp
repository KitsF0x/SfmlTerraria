#include "SandBlock.hpp"

SandBlock::SandBlock()
{
	shape.setFillColor(sf::Color::Yellow);
	shape.setSize(sf::Vector2f{ BLOCK_SIZE, BLOCK_SIZE });
}

sf::FloatRect SandBlock::getHitbox()
{
	return shape.getGlobalBounds();
}

void SandBlock::update(float deltaTime)
{
	if (getPosition() != shape.getPosition())
	{
		shape.setPosition(getPosition());
	}
}

void SandBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape);
}