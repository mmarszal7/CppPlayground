#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "Pixelate.cpp"
#include "WaveBlur.cpp"
#include "StormBlink.cpp"
#include "Edge.cpp"
#include "Geometry.cpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Shader", sf::Style::Titlebar | sf::Style::Close);

	Pixelate effect;
	//WaveBlur effect;
	//StormBlink effect;
	//Edge effect;
	Geometry effect;
	effect.load();

	sf::Clock clock;
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		float x = static_cast<float>(sf::Mouse::getPosition(window).x) / window.getSize().x;
		float y = static_cast<float>(sf::Mouse::getPosition(window).y) / window.getSize().y;
		effect.update(clock.getElapsedTime().asSeconds(), x, y);

		window.clear(sf::Color(255, 128, 0));
		window.draw(effect);
		window.display();
	}

	return EXIT_SUCCESS;
}

