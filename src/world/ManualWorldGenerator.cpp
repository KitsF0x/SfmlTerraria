#include "ManualWorldGenerator.hpp"

ManualWorldGenerator::ManualWorldGenerator(const std::vector<std::vector<std::uint32_t>>& numericIds)
	: numericIds(numericIds)
{
}

std::vector<std::shared_ptr<BaseBlock>> ManualWorldGenerator::generate(const sf::Vector2f& offset)
{
	std::vector<std::shared_ptr<BaseBlock>> toReturn;
	for (int y = 0; y < numericIds.size(); y++)
	{
		for (int x = 0; x < numericIds.at(y).size(); x++)
		{
			std::shared_ptr<BaseBlock> block;
			switch (numericIds.at(y).at(x))
			{
			case BlocksIdTable::GRASS_BLOCK_ID:
				block = std::make_shared<GrassBlock>();
				break;
			case BlocksIdTable::SAND_BLOCK_ID:
				block = std::make_shared<SandBlock>();
				break;
			case BlocksIdTable::WATER_BLOCK_ID:
				block = std::make_shared<WaterBlock>();
				break;
			case 0:
			default:
				continue;
			}
			block->setPosition(sf::Vector2f{
				BaseBlock::BLOCK_SIZE * x + offset.x,
				BaseBlock::BLOCK_SIZE * y + offset.y }
			);
			toReturn.push_back(block);
		}
	}
	return toReturn;
}