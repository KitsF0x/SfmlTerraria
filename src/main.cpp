#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GrassBlock.hpp"
#include "SandBlock.hpp"
#include "WaterBlock.hpp"
#include "GameObjectsManager.hpp"
#include "ManualWorldGenerator.hpp"

int main()
{
	sf::RenderWindow wnd{ sf::VideoMode{800, 600}, "Game window" };
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::ON_GROUND);
	GameObjectsManager manager;
	ManualWorldGenerator generator{ { {0,0,0,1,1,1,2,2,2} } };
	auto blocks = generator.generate(sf::Vector2f{ 0, 500 });
	for (auto& el : blocks)
	{
		manager.add(el);
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