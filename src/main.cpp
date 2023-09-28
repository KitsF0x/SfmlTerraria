#include <SFML/Graphics.hpp>
#include "Player.hpp"

int main()
{
	sf::RenderWindow wnd{ sf::VideoMode{800, 600}, "Game window" };
	Player player;
	player.gravityManager.setStatus(PlayerStatus::ON_GROUND);
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
		player.update(deltaTime);
		wnd.display();
	}
}