#include <SFML/Graphics.hpp>

class WaveBlur : public sf::Drawable
{
public:

	WaveBlur()
	{
	}

	bool load()
	{
		// Load the texture and initialize the sprite
		if (!m_texture.loadFromFile("resources/sfml.png"))
			return false;
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(30, 20);

		// Load the shader
		if (!m_shader.loadFromFile("resources/wave.vert", "resources/blur.frag"))
			return false;

		return true;
	}

	void update(float time, float x, float y)
	{
		m_shader.setUniform("wave_phase", time);
		m_shader.setUniform("wave_amplitude", sf::Vector2f(x * 40, y * 40));
		m_shader.setUniform("blur_radius", (x + y) * 0.008f);
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.shader = &m_shader;
		target.draw(m_sprite, states);
	}

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Shader m_shader;
};