#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int draw(int ifLower, int ifGreater)
{
	return rand() < RAND_MAX / 2 ? ifLower : ifGreater;
}

void update(sf::Shape& shape)
{
	shape.setRotation(
		shape.getRotation() + draw(-20, 20)
	);

	shape.setPosition(
		shape.getPosition().x + draw(-20, 20),
		shape.getPosition().y + draw(-20, 20)
	);

	shape.setScale(
		sf::Vector2f(draw(0.9, 1.1), draw(0.9, 1.1))
	);

	shape.setOutlineThickness(
		shape.getOutlineThickness() + draw(-1, 1)
	);

	shape.setOutlineColor(sf::Color(
		shape.getOutlineColor().r + draw(-1, 1),
		shape.getOutlineColor().g + draw(-1, 1),
		shape.getOutlineColor().b + draw(-1, 1))
	);
	shape.setFillColor(sf::Color(
		shape.getFillColor().r + draw(-1, 1),
		shape.getFillColor().g + draw(-1, 1),
		shape.getFillColor().b + draw(-1, 1))
	);
}

int main()
{
	srand(time(0));

	// Shapes
	//sf::CircleShape shape(80.f);
	sf::RectangleShape shape(sf::Vector2f(80, 80));

	// Color
	shape.setFillColor(sf::Color::Green);
	shape.setOutlineThickness(5.f);
	shape.setOutlineColor(sf::Color::Red);

	// Position
	shape.setPosition(400, 400);

	// Textures
	sf::Texture texture;
	texture.loadFromFile("texture.png");
	shape.setTexture(&texture);

	// Music
	sf::Music music;
	music.openFromFile("");
	music.setVolume(50);
	music.play();

	// Antialiasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Window
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML", sf::Style::Default, settings);
	sf::Event event;
	sf::Clock clock;

	window.setFramerateLimit(30);
	while (window.isOpen())
	{
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear();
		window.draw(shape);
		window.display();
		update(shape);

		std::cout << clock.getElapsedTime().asMilliseconds() << std::endl;
		clock.restart();
	}

	return 0;
}
