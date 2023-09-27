#include <SFML/Graphics.hpp>
#include "Player.hpp"

int main()
{
	sf::RenderWindow wnd{ sf::VideoMode{800, 600}, "Game window" };
	Player player;
	while (wnd.isOpen())
	{
		sf::Event evn;
		while (wnd.pollEvent(evn))
		{
			if (evn.type == sf::Event::Closed)
			{
				wnd.close();
			}
			wnd.clear(sf::Color::Magenta);
			wnd.draw(player);
			player.keyboardInputHandling();
			wnd.display();
		}
	}
}