#pragma once

#include <vector>
#include <memory>
#include "BaseBlock.hpp"

class IWorldGenerator
{
public:
	virtual std::vector<std::shared_ptr<BaseBlock>> generate(const sf::Vector2f& offset) = 0;
};