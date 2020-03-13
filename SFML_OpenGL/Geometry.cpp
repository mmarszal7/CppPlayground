#include <SFML/Graphics.hpp>

class Geometry : public sf::Drawable
{
public:

	Geometry() :
		m_pointCloud(sf::Points, 10000)
	{
	}

	bool load()
	{
		// Check if geometry shaders are supported
		if (!sf::Shader::isGeometryAvailable())
			return false;

		// Move the points in the point cloud to random positions
		for (std::size_t i = 0; i < 10000; i++)
		{
			// Spread the coordinates from -480 to +480
			// So they'll always fill the viewport at 800x600
			m_pointCloud[i].position.x = rand() % 960 - 480.f;
			m_pointCloud[i].position.y = rand() % 960 - 480.f;
		}

		// Load the texture
		if (!m_logoTexture.loadFromFile("resources/logo.png"))
			return false;

		// Load the shader
		if (!m_shader.loadFromFile("resources/billboard.vert", "resources/billboard.geom", "resources/billboard.frag"))
			return false;
		m_shader.setUniform("texture", sf::Shader::CurrentTexture);

		// Set the render resolution (used for proper scaling)
		m_shader.setUniform("resolution", sf::Vector2f(800, 600));

		return true;
	}

	void update(float time, float x, float y)
	{
		// Reset our transformation matrix
		m_transform = sf::Transform::Identity;
		// Move to the center of the window
		m_transform.translate(400, 300);
		// Rotate everything based on cursor position
		m_transform.rotate(x * 360.f);

		// Adjust billboard size to scale between 25 and 75
		float size = 25 + std::abs(y) * 50;

		// Update the shader parameter
		m_shader.setUniform("size", sf::Vector2f(size, size));
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// Prepare the render state
		states.shader = &m_shader;
		states.texture = &m_logoTexture;
		states.transform = m_transform;

		// Draw the point cloud
		target.draw(m_pointCloud, states);
	}

private:

	sf::Texture m_logoTexture;
	sf::Transform m_transform;
	sf::Shader m_shader;
	sf::VertexArray m_pointCloud;
};