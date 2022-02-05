#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"Learning SFML",sf::Style::Resize);
	sf::CircleShape circle(100.f);
	circle.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		sf::Event ev;
		while(window.pollEvent(ev))
		{
			if(ev.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		window.draw(circle);
		window.display();
	}
}
