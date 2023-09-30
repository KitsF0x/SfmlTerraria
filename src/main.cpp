#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "GrassBlock.hpp"

int main()
{
	sf::RenderWindow wnd{ sf::VideoMode{800, 600}, "Game window" };
	Player player;
	player.gravityManager.setStatus(PlayerStatus::ON_GROUND);

	GrassBlock block;
	block.setPosition(sf::Vector2f{ 100, 200 });

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
		wnd.draw(block);
		player.update(deltaTime);
		block.update(deltaTime);
		player.detectCollisionWithBlock(block);
		wnd.display();
	}
}