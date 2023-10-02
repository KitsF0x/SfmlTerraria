#pragma once

#include "IWorldGenerator.hpp"
#include "BlocksIdTable.hpp"

#include "GrassBlock.hpp"
#include "WaterBlock.hpp"
#include "SandBlock.hpp"

class ManualWorldGenerator : public IWorldGenerator
{
private:
	const std::vector<std::vector<std::uint32_t>> numericIds;
public:
	ManualWorldGenerator(const std::vector<std::vector<std::uint32_t>>& numericIds);
	std::vector<std::shared_ptr<BaseBlock>> generate(const sf::Vector2f& offset) override;
};