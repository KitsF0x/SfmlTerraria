#include <gtest/gtest.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include "AGameObject.hpp"

class TestGameObject : public AGameObject
{
public:
	TestGameObject()
	{
	}
	sf::FloatRect getHitbox() override
	{
		return shape.getGlobalBounds();
	}

	void update(float deltaTime) override
	{
		shape.setPosition(getPosition());
	}
protected:
	sf::RectangleShape shape{ sf::Vector2f{10, 10} };
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
	}
};

TEST(AGameObjectTest, can_detect_collision)
{
	// Arrange
	TestGameObject testGameObject;

	// Act
	bool collides = testGameObject.collidesTop(sf::FloatRect{
		testGameObject.getHitbox().left - 1,
		testGameObject.getHitbox().top - 1,
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});

	// Assert
	EXPECT_TRUE(collides);
}

TEST(AGameObjectTest, can_detect_top_collision)
{
	// Arrange
	TestGameObject testGameObject;

	// Act
	bool collides = testGameObject.collidesTop(sf::FloatRect{
		testGameObject.getHitbox().left,
		testGameObject.getHitbox().top - (testGameObject.getHitbox().height / 2),
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});

	// Assert
	EXPECT_TRUE(collides);
}

TEST(AGameObjectTest, can_detect_bottom_collision)
{
	// Arrange
	TestGameObject testGameObject;

	// Act
	bool collides = testGameObject.collidesBottom(sf::FloatRect{
		testGameObject.getHitbox().left,
		testGameObject.getHitbox().top + (testGameObject.getHitbox().height / 2),
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});

	// Assert
	EXPECT_TRUE(collides);
}

TEST(AGameObjectTest, when_colliding_with_top_is_true_colliding_with_bottom_should_be_false)
{
	// Arrange
	TestGameObject testGameObject;

	// Act
	bool collidesTop = testGameObject.collidesTop(sf::FloatRect{
		testGameObject.getHitbox().left,
		testGameObject.getHitbox().top - (testGameObject.getHitbox().height / 2),
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});
	bool collidesBottom = testGameObject.collidesBottom(sf::FloatRect{
		testGameObject.getHitbox().left,
		testGameObject.getHitbox().top - (testGameObject.getHitbox().height / 2),
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		}
	);

	// Assert
	EXPECT_TRUE(collidesTop);
	EXPECT_FALSE(collidesBottom);
}

TEST(AGameObjectTest, when_colliding_with_bottom_is_true_colliding_with_top_should_be_false)
{
	// Arrange
	TestGameObject testGameObject;

	// Act
	bool collidesBottom = testGameObject.collidesBottom(sf::FloatRect{
		testGameObject.getHitbox().left,
		testGameObject.getHitbox().top + (testGameObject.getHitbox().height / 2),
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});
	bool collidesTop = testGameObject.collidesTop(sf::FloatRect{
		testGameObject.getHitbox().left,
		testGameObject.getHitbox().top + (testGameObject.getHitbox().height / 2),
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});

	// Assert
	EXPECT_TRUE(collidesBottom);
	EXPECT_FALSE(collidesTop);
}

TEST(AGameObjectTest, can_detect_left_collision)
{
	// Arrange
	TestGameObject testGameObject;

	// Act
	bool collides = testGameObject.collidesLeft(sf::FloatRect{
		testGameObject.getHitbox().left - (testGameObject.getHitbox().width / 2),
		testGameObject.getHitbox().top,
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});

	// Assert
	EXPECT_TRUE(collides);
}

TEST(AGameObjectTest, can_detect_right_collision)
{
	// Arrange
	TestGameObject testGameObject;

	// Act
	bool collides = testGameObject.collidesRight(sf::FloatRect{
		testGameObject.getHitbox().left + (testGameObject.getHitbox().width / 2),
		testGameObject.getHitbox().top,
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});

	// Assert
	EXPECT_TRUE(collides);
}

TEST(AGameObjectTest, when_colliding_with_right_is_true_colliding_with_left_should_be_false)
{
	// Arrange
	TestGameObject testGameObject;

	// Act
	bool collidesRight = testGameObject.collidesRight(sf::FloatRect{
		testGameObject.getHitbox().left + (testGameObject.getHitbox().width / 2),
		testGameObject.getHitbox().top,
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});
	bool collidesLeft = testGameObject.collidesLeft(sf::FloatRect{
		testGameObject.getHitbox().left + (testGameObject.getHitbox().width / 2),
		testGameObject.getHitbox().top,
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});

	// Assert
	EXPECT_TRUE(collidesRight);
	EXPECT_FALSE(collidesLeft);
}

TEST(AGameObjectTest, when_colliding_with_left_is_true_colliding_with_right_should_be_false)
{
	// Arrange
	TestGameObject testGameObject;

	// Act
	bool collidesRight = testGameObject.collidesRight(sf::FloatRect{
		testGameObject.getHitbox().left - (testGameObject.getHitbox().width / 2),
		testGameObject.getHitbox().top,
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});
	bool collidesLeft = testGameObject.collidesLeft(sf::FloatRect{
		testGameObject.getHitbox().left - (testGameObject.getHitbox().width / 2),
		testGameObject.getHitbox().top,
		testGameObject.getHitbox().width,
		testGameObject.getHitbox().height
		});

	// Assert
	EXPECT_TRUE(collidesLeft);
	EXPECT_FALSE(collidesRight);
}

TEST(AGameObjectTest, can_move_object_to_the_north)
{
	// Arrange
	TestGameObject testGameObject;
	testGameObject.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	testGameObject.moveGameObject(Direction::NORTH, 1.0f, 1.0f);

	// Assert
	EXPECT_EQ(testGameObject.getPosition(), sf::Vector2f(0.0f, -1.0f));
}

TEST(AGameObjectTest, can_move_object_to_the_south)
{
	// Arrange
	TestGameObject testGameObject;
	testGameObject.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	testGameObject.moveGameObject(Direction::SOUTH, 1.0f, 1.0f);

	// Assert
	EXPECT_EQ(testGameObject.getPosition(), sf::Vector2f(0.0f, 1.0f));
}

TEST(AGameObjectTest, can_move_object_to_the_east)
{
	// Arrange
	TestGameObject testGameObject;
	testGameObject.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	testGameObject.moveGameObject(Direction::EAST, 1.0f, 1.0f);

	// Assert
	EXPECT_EQ(testGameObject.getPosition(), sf::Vector2f(1.0f, 0.0f));
}

TEST(AGameObjectTest, can_move_player_to_the_west)
{
	// Arrange
	TestGameObject testGameObject;
	testGameObject.setPosition(sf::Vector2f{ 0.0f, 0.0f });

	// Act
	testGameObject.moveGameObject(Direction::WEST, 1.0f, 1.0f);

	// Assert
	EXPECT_EQ(testGameObject.getPosition(), sf::Vector2f(-1.0f, 0.0f));
}