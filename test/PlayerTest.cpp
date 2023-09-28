#include <gtest/gtest.h>

#include <memory>
#include "Player.hpp"
#include "GravityManager.hpp"

TEST(PlayerTest, can_move_player_to_the_north)
{
	// Arrange
	Player player;
	player.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	player.movePlayer(Direction::NORTH, 1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, -GravityManager::BASE_VERTICAL_SPEED));
}

TEST(PlayerTest, can_move_player_to_the_south)
{
	// Arrange
	Player player;
	player.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	player.movePlayer(Direction::SOUTH, 1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, GravityManager::BASE_VERTICAL_SPEED));
}

TEST(PlayerTest, can_move_player_to_the_east)
{
	// Arrange
	Player player;
	player.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	player.movePlayer(Direction::EAST, 1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(GravityManager::BASE_HORIZONTAL_SPEED, 0.0f));
}

TEST(PlayerTest, can_move_player_to_the_west)
{
	// Arrange
	Player player;
	player.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	player.movePlayer(Direction::WEST, 1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(-GravityManager::BASE_HORIZONTAL_SPEED, 0.0f));
}

TEST(PlayerTest, can_calculate_player_speed_with_delta_time)
{
	// Arrange
	Player player;

	// Act
	player.movePlayer(Direction::SOUTH, 0.1f);

	// Assert
	EXPECT_EQ(player.getPosition().y, (GravityManager::BASE_VERTICAL_SPEED / 10));
}

TEST(PlayerTest, can_player_fall)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(PlayerStatus::FALLING);

	// Act
	player.gravityManager.handleFall(1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(player.getPosition().x, GravityManager::BASE_VERTICAL_SPEED));
}

TEST(PlayerTest, can_player_jump)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(PlayerStatus::ON_GROUND);
	player.gravityManager.triggerJump();

	// Act
	player.gravityManager.handleJump(1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(player.getPosition().x, -GravityManager::BASE_VERTICAL_SPEED));
}

TEST(PlayerTest, player_cannot_fall_when_status_is_on_ground)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(PlayerStatus::ON_GROUND);

	// Act
	player.gravityManager.handleFall(1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, 0.0f));
}

TEST(PlayerTest, player_cannot_jump_when_status_is_falling)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(PlayerStatus::FALLING);

	// Act
	player.gravityManager.handleJump(1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, 0.0f));
}

TEST(PlayerTest, player_cannot_fall_when_status_is_jumping)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(PlayerStatus::JUMPING);

	// Act
	player.gravityManager.handleFall(1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, 0.0f));
}

TEST(PlayerTest, player_can_trigger_jump_when_status_is_on_ground)
{
	// Arrange
	Player player;
	player.gravityManager.setStatus(PlayerStatus::ON_GROUND);
	player.gravityManager.triggerJump();

	// Act
	player.gravityManager.handleJump(1.0f);

	// Assert
	EXPECT_EQ(player.gravityManager.getJumpStepCounter(), GravityManager::JUMP_STEP_COUNTER_INIT_VALUE - 1);
}

TEST(PlayerTest, when_jump_is_triggered_jump_step_counter_is_set_to_constant_value)
{
	// Arrange
	Player player;

	// Act
	player.gravityManager.triggerJump();

	// Assert
	EXPECT_EQ(player.gravityManager.getJumpStepCounter(), GravityManager::JUMP_STEP_COUNTER_INIT_VALUE);
}

TEST(PlayerTest, when_jump_is_triggered_jump_status_should_be_set_to_jumping)
{
	// Arrange
	Player player;

	// Act
	player.gravityManager.triggerJump();

	// Assert
	EXPECT_EQ(player.gravityManager.getStatus(), PlayerStatus::JUMPING);
}

TEST(PlayerTest, when_status_is_jumping_jump_step_counter_should_be_decremented_after_each_jump)
{
	// Arrange
	Player player;

	// Act
	player.gravityManager.triggerJump();
	player.gravityManager.handleJump(1.0f);

	// Assert
	EXPECT_EQ(player.gravityManager.getJumpStepCounter(), GravityManager::JUMP_STEP_COUNTER_INIT_VALUE - 1);
}

TEST(PlayerTest, jump_step_counter_decrementing_should_stop_at_zero)
{
	// Arrange
	Player player;

	// Act
	player.gravityManager.triggerJump();
	for (int i = 0; i < GravityManager::JUMP_STEP_COUNTER_INIT_VALUE + 10 /*to make sure it stops at zero*/; i++)
	{
		player.gravityManager.handleJump(1.0f);
	}

	// Assert
	EXPECT_EQ(player.gravityManager.getJumpStepCounter(), 0);
}

TEST(PlayerTest, when_jump_step_counter_reach_zero_status_should_be_set_to_falling)
{
	// Arrange
	Player player;

	// Act
	player.gravityManager.triggerJump();
	for (int i = 0; i < GravityManager::JUMP_STEP_COUNTER_INIT_VALUE + 10; i++)
	{
		player.gravityManager.handleJump(1.0f);
	}

	// Assert
	EXPECT_EQ(player.gravityManager.getStatus(), PlayerStatus::FALLING);
}

TEST(PlayerTest, when_status_is_on_ground_jump_and_fall_handling_should_not_move_player)
{
	// Arrange
	Player player;

	// Act
	player.gravityManager.handleFall(1.0f);
	player.gravityManager.handleJump(1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, 0.0f));
}