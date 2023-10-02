#include <gtest/gtest.h>
#include <vector>
#include "BaseBlock.hpp"
#include "WaterBlock.hpp"
#include "GrassBlock.hpp"
#include "SandBlock.hpp"

#include "ManualWorldGenerator.hpp"

TEST(WorldGenerationTest, can_map_2d_vector_of_ints_into_vector_of_blocks)
{
	// Arrange
	ManualWorldGenerator generator{ {
		{BlocksIdTable::GRASS_BLOCK_ID, BlocksIdTable::GRASS_BLOCK_ID, BlocksIdTable::GRASS_BLOCK_ID},
		{BlocksIdTable::SAND_BLOCK_ID, BlocksIdTable::SAND_BLOCK_ID, BlocksIdTable::SAND_BLOCK_ID},
		{BlocksIdTable::WATER_BLOCK_ID, BlocksIdTable::WATER_BLOCK_ID, BlocksIdTable::WATER_BLOCK_ID}
		} };

	// Act
	std::vector<std::shared_ptr<BaseBlock>> blocks = generator.generate(sf::Vector2f{ 0,0 });

	// Assert
	EXPECT_EQ(blocks.size(), 9);
	EXPECT_NE(dynamic_cast<GrassBlock*>(blocks.at(0).get()), nullptr);
	EXPECT_NE(dynamic_cast<GrassBlock*>(blocks.at(1).get()), nullptr);
	EXPECT_NE(dynamic_cast<GrassBlock*>(blocks.at(2).get()), nullptr);

	EXPECT_NE(dynamic_cast<SandBlock*>(blocks.at(3).get()), nullptr);
	EXPECT_NE(dynamic_cast<SandBlock*>(blocks.at(4).get()), nullptr);
	EXPECT_NE(dynamic_cast<SandBlock*>(blocks.at(5).get()), nullptr);

	EXPECT_NE(dynamic_cast<WaterBlock*>(blocks.at(6).get()), nullptr);
	EXPECT_NE(dynamic_cast<WaterBlock*>(blocks.at(7).get()), nullptr);
	EXPECT_NE(dynamic_cast<WaterBlock*>(blocks.at(8).get()), nullptr);
}

TEST(WorldGenerationTest, can_calculate_position_for_each_block_in_map_method)
{
	// Arrange
	ManualWorldGenerator generator{ {
		{BlocksIdTable::GRASS_BLOCK_ID, BlocksIdTable::SAND_BLOCK_ID, BlocksIdTable::WATER_BLOCK_ID},
		{BlocksIdTable::GRASS_BLOCK_ID, BlocksIdTable::SAND_BLOCK_ID, BlocksIdTable::WATER_BLOCK_ID},
		} };

	// Act
	std::vector<std::shared_ptr<BaseBlock>> blocks = generator.generate(sf::Vector2f{ 0,0 });

	// Assert
	EXPECT_EQ(blocks.at(0)->getPosition(), sf::Vector2f(0, 0));
	EXPECT_EQ(blocks.at(1)->getPosition(), sf::Vector2f(BaseBlock::BLOCK_SIZE, 0));
	EXPECT_EQ(blocks.at(2)->getPosition(), sf::Vector2f(BaseBlock::BLOCK_SIZE * 2, 0));
	EXPECT_EQ(blocks.at(3)->getPosition(), sf::Vector2f(0, BaseBlock::BLOCK_SIZE));
	EXPECT_EQ(blocks.at(4)->getPosition(), sf::Vector2f(BaseBlock::BLOCK_SIZE, BaseBlock::BLOCK_SIZE));
	EXPECT_EQ(blocks.at(5)->getPosition(), sf::Vector2f(BaseBlock::BLOCK_SIZE * 2, BaseBlock::BLOCK_SIZE));
}

TEST(WorldGenerationTest, when_passed_offset_in_map_method_should_add_offset_for_each_block)
{
	// Arrange
	ManualWorldGenerator generator{ {
		{BlocksIdTable::GRASS_BLOCK_ID, BlocksIdTable::SAND_BLOCK_ID, BlocksIdTable::WATER_BLOCK_ID},
		{BlocksIdTable::GRASS_BLOCK_ID, BlocksIdTable::SAND_BLOCK_ID, BlocksIdTable::WATER_BLOCK_ID},
		} };

	// Act
	std::vector<std::shared_ptr<BaseBlock>> blocks = generator.generate(sf::Vector2f{ 23, 10 });

	// Assert
	EXPECT_EQ(blocks.at(0)->getPosition(), sf::Vector2f(23, 10));
	EXPECT_EQ(blocks.at(1)->getPosition(), sf::Vector2f(BaseBlock::BLOCK_SIZE + 23, 10));
	EXPECT_EQ(blocks.at(2)->getPosition(), sf::Vector2f(BaseBlock::BLOCK_SIZE * 2 + 23, 10));
	EXPECT_EQ(blocks.at(3)->getPosition(), sf::Vector2f(23, BaseBlock::BLOCK_SIZE + 10));
	EXPECT_EQ(blocks.at(4)->getPosition(), sf::Vector2f(BaseBlock::BLOCK_SIZE + 23, BaseBlock::BLOCK_SIZE + 10));
	EXPECT_EQ(blocks.at(5)->getPosition(), sf::Vector2f(BaseBlock::BLOCK_SIZE * 2 + 23, BaseBlock::BLOCK_SIZE + 10));
}

TEST(WorldGenerationTest, when_id_is_zero_block_should_be_ignored)
{
	// Arrange
	ManualWorldGenerator generator{ {
		{BlocksIdTable::GRASS_BLOCK_ID, 0, BlocksIdTable::WATER_BLOCK_ID}
	} };

	// Act
	auto blocks = generator.generate(sf::Vector2f{ 0,0 });

	// Assert
	EXPECT_EQ(blocks.size(), 2);
}