#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GrassBlock.hpp"

int main()
{
	sf::RenderWindow wnd{ sf::VideoMode{800, 600}, "Game window" };
	Player player;
	player.gravityManager.setStatus(GameObjectStatus::ON_GROUND);

	std::vector<GrassBlock> blocks{ 10 };
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks.at(i).setPosition(sf::Vector2f{ 0 + i * GrassBlock::BLOCK_SIZE, 500 });
	}

	sf::Clock clock;
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
		float deltaTime = clock.restart().asSeconds();
		wnd.clear(sf::Color::Magenta);
		wnd.draw(player);
		for (auto& el : blocks)
		{
			wnd.draw(el);
			el.update(deltaTime);
			player.detectCollisionWithBlock(el);
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
		player.update(deltaTime);
		player.detectStandingOnAnyBlockFromVector(blocks);
		wnd.display();
	}
}