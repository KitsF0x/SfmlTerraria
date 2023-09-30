#include <gtest/gtest.h>

#include <memory>
#include "Player.hpp"
#include "GravityManager.hpp"
#include "GrassBlock.hpp"

TEST(PlayerTest, can_calculate_player_speed_with_delta_time)
{
	// Arrange
	Player player;

	// Act
	player.moveGameObject(Direction::SOUTH, 0.1f, Player::PLAYER_SPEED);

	// Assert
	EXPECT_EQ(player.getPosition().y, (Player::PLAYER_SPEED / 10));
}

TEST(PlayerTest, can_player_fall)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::FALLING);

	// Act
	player.gravityManager.handleFall(1.0f, Player::PLAYER_SPEED);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(player.getPosition().x, Player::PLAYER_SPEED));
}

TEST(PlayerTest, can_player_jump)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::ON_GROUND);
	player.gravityManager.triggerJump(10);

	// Act
	player.gravityManager.handleJump(1.0f, Player::PLAYER_SPEED);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(player.getPosition().x, -Player::PLAYER_SPEED));
}

TEST(PlayerTest, player_cannot_fall_when_status_is_on_ground)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::ON_GROUND);

	// Act
	player.gravityManager.handleFall(1.0f, Player::PLAYER_SPEED);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, 0.0f));
}

TEST(PlayerTest, player_cannot_jump_when_status_is_falling)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::FALLING);

	// Act
	player.gravityManager.handleJump(1.0f, Player::PLAYER_SPEED);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, 0.0f));
}

TEST(PlayerTest, player_cannot_fall_when_status_is_jumping)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::JUMPING);

	// Act
	player.gravityManager.handleFall(1.0f, Player::PLAYER_SPEED);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, 0.0f));
}

TEST(PlayerTest, player_can_trigger_jump_when_status_is_on_ground)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::ON_GROUND);
	player.gravityManager.triggerJump(10);

	// Act
	player.gravityManager.handleJump(1.0f, Player::PLAYER_SPEED);

	// Assert
	EXPECT_EQ(player.gravityManager.getJumpStepCounter(), 9);
}

TEST(PlayerTest, when_jump_is_triggered_jump_status_should_be_set_to_jumping)
{
	// Arrange
	Player player;

	// Act
	player.gravityManager.triggerJump(10);

	// Assert
	EXPECT_EQ(player.gravityManager.getStatus(), GameObjectStatus::JUMPING);
}

TEST(PlayerTest, when_status_is_jumping_jump_step_counter_should_be_decremented_after_each_jump)
{
	// Arrange
	Player player;

	// Act
	player.gravityManager.triggerJump(10);
	player.gravityManager.handleJump(1.0f, Player::PLAYER_SPEED);

	// Assert
	EXPECT_EQ(player.gravityManager.getJumpStepCounter(), 9);
}

TEST(PlayerTest, jump_step_counter_decrementing_should_stop_at_zero)
{
	// Arrange
	Player player;

	// Act
	player.gravityManager.triggerJump(10);
	for (int i = 0; i < 10; i++)
	{
		player.gravityManager.handleJump(1.0f, Player::PLAYER_SPEED);
	}

	// Assert
	EXPECT_EQ(player.gravityManager.getJumpStepCounter(), 0);
}

TEST(PlayerTest, when_jump_step_counter_reach_zero_status_should_be_set_to_falling)
{
	// Arrange
	Player player;

	// Act
	player.gravityManager.triggerJump(10);
	for (int i = 0; i < 11; i++)
	{
		player.gravityManager.handleJump(1.0f, Player::PLAYER_SPEED);
	}

	// Assert
	EXPECT_EQ(player.gravityManager.getStatus(), GameObjectStatus::FALLING);
}

TEST(PlayerTest, when_status_is_on_ground_jump_and_fall_handling_should_not_move_player)
{
	// Arrange
	Player player;

	// Act
	player.gravityManager.handleFall(1.0f, Player::PLAYER_SPEED);
	player.gravityManager.handleJump(1.0f, Player::PLAYER_SPEED);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, 0.0f));
}

TEST(PlayerTest, can_detect_collision_with_block_and_set_status_to_on_ground_when_status_is_falling)
{
	// Arrange
	Player player;
	std::shared_ptr<GrassBlock> block = std::make_shared<GrassBlock>();

	player.setPosition(block->getHitbox().left, -block->getHitbox().top - 1);
	player.gravityManager.setStatus(GameObjectStatus::FALLING);
	player.update(1.0f);

	// Act
	player.checkBottomCollisionsAndUpdateStatus(block);

	// Assert
	EXPECT_EQ(player.gravityManager.getStatus(), GameObjectStatus::ON_GROUND);
}

TEST(PlayerTest, when_player_is_not_standing_on_any_block_from_vector_then_status_should_be_set_to_falling)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::ON_GROUND);
	std::vector<std::shared_ptr<AGameObject>> blocks{ 2 };
	blocks.at(0) = std::make_shared<GrassBlock>();
	blocks.at(1) = std::make_shared<GrassBlock>();
	player.setPosition(1000.0f, 1000.0f);

	// Act
	player.checkBottomCollisionsAndUpdateStatus(blocks);

	// Assert
	EXPECT_EQ(player.gravityManager.getStatus(), GameObjectStatus::FALLING);
}

TEST(PlayerTest, when_player_is_standing_on_any_block_from_vector_then_status_should_be_set_to_on_ground)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::FALLING);
	std::vector<std::shared_ptr<AGameObject>> blocks{ 2 };
	blocks.at(0) = std::make_shared<GrassBlock>();
	blocks.at(1) = std::make_shared<GrassBlock>();
	player.setPosition(0.0f, 500.0f);
	blocks.at(0)->setPosition(player.getPosition() + sf::Vector2f{ 0, Player::PLAYER_SIZE.y - 1 });
	player.update(1.0f);
	blocks.at(0)->update(1.0f);

	// Act
	player.checkBottomCollisionsAndUpdateStatus(blocks);

	// Assert
	EXPECT_EQ(player.gravityManager.getStatus(), GameObjectStatus::ON_GROUND);
}

TEST(PlayerTest, when_detected_collision_with_any_block_is_true_and_jump_counter_is_zero_status_should_be_set_to_falling)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::FALLING);
	std::vector<std::shared_ptr<AGameObject>> blocks{ 2 };
	blocks.at(0) = std::make_shared<GrassBlock>();
	blocks.at(1) = std::make_shared<GrassBlock>();
	player.setPosition(0.0f, 500.0f);
	blocks.at(0)->setPosition(player.getPosition() + sf::Vector2f{ 0, Player::PLAYER_SIZE.y - 1 });
	for (int i = 0; i < 10;i++)
	{
		player.update(1.0f);
	}
	blocks.at(0)->update(1.0f);

	// Act
	player.checkBottomCollisionsAndUpdateStatus(blocks);

	// Assert
	EXPECT_EQ(player.gravityManager.getStatus(), GameObjectStatus::FALLING);
}