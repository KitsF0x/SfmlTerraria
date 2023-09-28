#include <gtest/gtest.h>

#include <memory>
#include "Player.hpp"

TEST(PlayerTest, can_move_player_to_the_north)
{
	// Arrange
	Player player;
	player.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	player.movePlayer(Direction::NORTH, 1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, -Player::PLAYER_BASE_SPEED));
}

TEST(PlayerTest, can_move_player_to_the_south)
{
	// Arrange
	Player player;
	player.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	player.movePlayer(Direction::SOUTH, 1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(0.0f, Player::PLAYER_BASE_SPEED));
}

TEST(PlayerTest, can_move_player_to_the_east)
{
	// Arrange
	Player player;
	player.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	player.movePlayer(Direction::EAST, 1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(Player::PLAYER_BASE_SPEED, 0.0f));
}

TEST(PlayerTest, can_move_player_to_the_west)
{
	// Arrange
	Player player;
	player.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	player.movePlayer(Direction::WEST, 1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(-Player::PLAYER_BASE_SPEED, 0.0f));
}

TEST(PlayerTest, can_calculate_player_speed_with_delta_time)
{
	// Arrange
	Player player;

	// Act
	player.movePlayer(Direction::SOUTH, 0.1f);

	// Assert
	EXPECT_EQ(player.getPosition().y, (Player::PLAYER_BASE_SPEED / 10));
}

TEST(PlayerTest, can_player_fall)
{
	// Arrange
	Player player;

	// Act
	player.fall(1.0f);

	// Assert
	EXPECT_EQ(player.getPosition(), sf::Vector2f(player.getPosition().x, Player::PLAYER_BASE_SPEED));
}