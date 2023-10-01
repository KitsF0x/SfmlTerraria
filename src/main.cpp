#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GrassBlock.hpp"
#include "SandBlock.hpp"
#include "WaterBlock.hpp"
#include "GameObjectsManager.hpp"

int main()
{
	sf::RenderWindow wnd{ sf::VideoMode{800, 600}, "Game window" };
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::ON_GROUND);
	GameObjectsManager manager;

	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<AGameObject> obj;
		switch (i % 3)
		{
		case 0:
			obj = std::make_shared<SandBlock>();
			break;
		case 1:
			obj = std::make_shared<GrassBlock>();
			break;
		case 2:
			obj = std::make_shared<WaterBlock>();
			break;
		}
		obj->setPosition(sf::Vector2f{ 0 + i * BaseBlock::BLOCK_SIZE, 500 });
		manager.add(obj);
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
		manager.update(deltaTime);
		manager.render(wnd);
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
		player.checkBottomCollisionsAndUpdateStatus(manager.getVector());
		player.update(deltaTime);
		wnd.display();
		deltaTime = clock.restart().asSeconds();
	}
}