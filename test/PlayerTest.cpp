#include <gtest/gtest.h>

#include <memory>
#include "Player.hpp"

TEST(PlayerTest, is_player_instance_of_sf_rectangle_shape)
{
	// Arrange
	std::unique_ptr<Player> player = std::make_unique<Player>();

	// Act
	bool isInstanceOfRectangleShape = (dynamic_cast<sf::RectangleShape*>(player.get())) ? true : false;

	// Assert
	EXPECT_TRUE(isInstanceOfRectangleShape);
}

TEST(PlayerTest, can_set_default_values_when_created_new_player_object)
{
	// Arrange
	Player player;

	// Act
	sf::Vector2f size = player.getSize();
	sf::Color color = player.getFillColor();

	// Assert
	EXPECT_EQ(size, Player::PLAYER_SIZE);
	EXPECT_EQ(color, Player::PLAYER_COLOR);
}

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