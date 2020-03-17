#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 1500.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 1024), "SFML Game", sf::Style::Close | sf::Style::Resize);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

	sf::Texture texture;
	texture.loadFromFile("spritesheet.png");
	Player player(&texture, sf::Vector2u(3, 4), 0.15f, 500.0f);

	std::vector<Platform> platforms;
	platforms.push_back(Platform(nullptr, sf::Vector2f(400.f, 200.f), sf::Vector2f(500.f, 200.f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(2000.f, 10.f), sf::Vector2f(0.f, 500.f)));

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case::sf::Event::Resized:
				ResizeView(window, view);
				break;
			}
		}

		window.clear(sf::Color(150, 150, 150));

		player.Update(deltaTime);

		auto collider = player.GetCollider();
		sf::Vector2f direction;
		for (Platform& platform : platforms) {
			if (platform.GetCollider().CheckCollision(collider, direction, 1.0f))
				player.OnCollision(direction);

			platform.Draw(window);
		}
		player.Draw(window);

		view.setCenter(player.GetPostition());
		window.setView(view);

		window.display();
	}

	return 0;
}