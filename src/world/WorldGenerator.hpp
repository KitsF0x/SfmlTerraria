#pragma once

#include <cstdint>
#include "GrassBlock.hpp"
#include "WaterBlock.hpp"
#include "SandBlock.hpp"
#include <vector>

class WorldGenerator
{
public:
	static const std::uint32_t GRASS_BLOCK_ID;
	static const std::uint32_t SAND_BLOCK_ID;
	static const std::uint32_t WATER_BLOCK_ID;

	std::vector<std::shared_ptr<BaseBlock>> map(
		const std::vector<std::vector<std::uint32_t>>& numericIds,
		const sf::Vector2f& offset = sf::Vector2f{ 0.0f,0.0f }
	);
};