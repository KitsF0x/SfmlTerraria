#include <gtest/gtest.h>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "AGameObject.hpp"
#include "GameObjectsManager.hpp"

class TestGameObject : public AGameObject
{
public:
	TestGameObject()
	{
		shape.setFillColor(sf::Color::Yellow);
	}
	sf::FloatRect getHitbox() override
	{
		return shape.getGlobalBounds();
	}

	void update(float deltaTime) override
	{
		updateCheck = true;
	}
	bool updateCheck{ false };
protected:
	sf::RectangleShape shape{ sf::Vector2f{10, 10} };
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(shape);
	}
};

TEST(GameObjectsManagerTest, can_add_objects_to_manager_and_increase_its_size)
{
	// Arrange
	GameObjectsManager gameObjectsManager;

	// Act
	gameObjectsManager.add(std::make_shared<TestGameObject>());

	// Assert
	EXPECT_EQ(gameObjectsManager.size(), 1);
}