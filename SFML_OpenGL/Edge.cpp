#include <SFML/Graphics.hpp>

class Edge : public sf::Drawable
{
public:

	Edge() 
	{
	}

	bool load()
	{
		// Create the off-screen surface
		if (!m_surface.create(800, 600))
			return false;
		m_surface.setSmooth(true);

		// Load the textures
		if (!m_backgroundTexture.loadFromFile("resources/sfml.png"))
			return false;
		m_backgroundTexture.setSmooth(true);
		if (!m_entityTexture.loadFromFile("resources/devices.png"))
			return false;
		m_entityTexture.setSmooth(true);

		// Initialize the background sprite
		m_backgroundSprite.setTexture(m_backgroundTexture);
		m_backgroundSprite.setPosition(135, 100);

		// Load the moving entities
		for (int i = 0; i < 6; ++i)
		{
			sf::Sprite entity(m_entityTexture, sf::IntRect(96 * i, 0, 96, 96));
			m_entities.push_back(entity);
		}

		// Load the shader
		if (!m_shader.loadFromFile("resources/edge.frag", sf::Shader::Fragment))
			return false;
		m_shader.setUniform("texture", sf::Shader::CurrentTexture);

		return true;
	}

	void update(float time, float x, float y)
	{
		m_shader.setUniform("edge_threshold", 1 - (x + y) / 2);

		// Update the position of the moving entities
		for (std::size_t i = 0; i < m_entities.size(); ++i)
		{
			sf::Vector2f position;
			position.x = std::cos(0.25f * (time * i + (m_entities.size() - i))) * 300 + 350;
			position.y = std::sin(0.25f * (time * (m_entities.size() - i) + i)) * 200 + 250;
			m_entities[i].setPosition(position);
		}

		// Render the updated scene to the off-screen surface
		m_surface.clear(sf::Color::White);
		m_surface.draw(m_backgroundSprite);
		for (std::size_t i = 0; i < m_entities.size(); ++i)
			m_surface.draw(m_entities[i]);
		m_surface.display();
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.shader = &m_shader;
		target.draw(sf::Sprite(m_surface.getTexture()), states);
	}

private:

	sf::RenderTexture m_surface;
	sf::Texture m_backgroundTexture;
	sf::Texture m_entityTexture;
	sf::Sprite m_backgroundSprite;
	std::vector<sf::Sprite> m_entities;
	sf::Shader m_shader;
};