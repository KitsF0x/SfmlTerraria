#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow wnd{ sf::VideoMode{800, 600}, "Game window" };
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
			wnd.display();
		}
	}
}