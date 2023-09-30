#include "GrassBlock.hpp"

GrassBlock::GrassBlock()
{
	dirtPart.setFillColor(sf::Color{ 110, 40, 30 });
	dirtPart.setSize(sf::Vector2f{ BLOCK_SIZE, BLOCK_SIZE });

	grassPart.setFillColor(sf::Color{ 87, 176, 35 });
	grassPart.setSize(sf::Vector2f{ BLOCK_SIZE, BLOCK_SIZE / 5 });
}

sf::FloatRect GrassBlock::getHitbox()
{
	return dirtPart.getGlobalBounds();
}

void GrassBlock::update(float deltaTime)
{
	if (getPosition() != dirtPart.getPosition())
	{
		dirtPart.setPosition(getPosition());
		grassPart.setPosition(getPosition());
	}
}

void GrassBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(dirtPart);
	target.draw(grassPart);
}