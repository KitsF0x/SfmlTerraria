#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GrassBlock.hpp"
#include "SandBlock.hpp"
#include "WaterBlock.hpp"

int main()
{
	sf::RenderWindow wnd{ sf::VideoMode{800, 600}, "Game window" };
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::ON_GROUND);

	std::vector < std::shared_ptr<AGameObject>> blocks{ 10 };
	for (int i = 0; i < blocks.size(); i++)
	{
		switch (i % 3)
		{
		case 0:
			blocks.at(i) = std::make_shared<SandBlock>();
			break;
		case 1:
			blocks.at(i) = std::make_shared<GrassBlock>();
			break;
		case 2:
			blocks.at(i) = std::make_shared<WaterBlock>();
			break;
		}
		blocks.at(i)->setPosition(sf::Vector2f{ 0 + i * GrassBlock::BLOCK_SIZE, 500 });
	}

	sf::Clock clock;
	float deltaTime = 1.0f;
	wnd.setFramerateLimit(50);
	while (wnd.isOpen())
	{
		sf::Event evn;
		while (wnd.pollEvent(evn))
		{
			if (evn.type == sf::Event::Closed)
			{
				wnd.close();
			}
		}
		wnd.clear(sf::Color::Magenta);
		wnd.draw(player);
		for (auto& el : blocks)
		{
			wnd.draw(*el.get());
			el->update(deltaTime);
			player.checkBottomCollisionsAndUpdateStatus(el);
		}
		if (player.gravityManager.getStatus() == GameObjectStatus::ON_GROUND)
		{
			std::cout << "On ground" << std::endl;
		}
		if (player.gravityManager.getStatus() == GameObjectStatus::FALLING)
		{
			std::cout << "Falling" << std::endl;
		}
		if (player.gravityManager.getStatus() == GameObjectStatus::JUMPING)
		{
			std::cout << "Jumping" << std::endl;
		}
		player.checkBottomCollisionsAndUpdateStatus(blocks);
		player.update(deltaTime);
		wnd.display();
		deltaTime = clock.restart().asSeconds();
	}
}