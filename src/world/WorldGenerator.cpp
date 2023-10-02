#include "WorldGenerator.hpp"

const std::uint32_t WorldGenerator::AIR_BLOCK_ID{ 0 };
const std::uint32_t WorldGenerator::GRASS_BLOCK_ID{ 1 };
const std::uint32_t WorldGenerator::SAND_BLOCK_ID{ 2 };
const std::uint32_t WorldGenerator::WATER_BLOCK_ID{ 3 };

std::vector<std::shared_ptr<BaseBlock>> WorldGenerator::map(
	const std::vector<std::vector<std::uint32_t>>& numericIds,
	const sf::Vector2f& offset
)
{
	std::vector<std::shared_ptr<BaseBlock>> toReturn;
	for (int y = 0; y < numericIds.size(); y++)
	{
		for (int x = 0; x < numericIds.at(y).size(); x++)
		{
			std::shared_ptr<BaseBlock> block;
			switch (numericIds.at(y).at(x))
			{
			case GRASS_BLOCK_ID:
				block = std::make_shared<GrassBlock>();
				break;
			case SAND_BLOCK_ID:
				block = std::make_shared<SandBlock>();
				break;
			case WATER_BLOCK_ID:
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