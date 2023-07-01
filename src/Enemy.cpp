#pragma once
#include <PLAYER.hpp>
#include <MAP.hpp>
#include <SFML/Graphics.hpp>
#include <Enemy.h>

namespace other {

	ENEMY::ENEMY(sf::Texture& image, Globals& map, int x, int y) {
		m_sprite.setTexture(image);
		m_rect = sf::FloatRect(x, y, 32, 32);
		m_x = m_y = 0.1;
		m_currentFrame = 0;
		m_map = &map;
		life = true;
	}
	void ENEMY::update(float time)
	{
		m_rect.left += m_x * time;

		Collision();

		m_currentFrame += time * 0.005;
		if (m_currentFrame > 2) m_currentFrame -= 2;

		m_sprite.setTextureRect(sf::IntRect(1 * static_cast<int>(m_currentFrame), 0, 32, 32));
		if (!life) {
			m_sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
		}


		m_sprite.setPosition(m_rect.left - m_offsetx, m_rect.top - m_offsety);

	}

	void ENEMY::Collision()
	{

		for (int i = m_rect.top / 32; i < (m_rect.top + m_rect.height) / 32; i++)
			for (int j = m_rect.left / 32; j < (m_rect.left + m_rect.width) / 32; j++)
				if ((m_map->TileMap[i][j] == 'Z') || (m_map->TileMap[i][j] == 'B'))
				{
					if (m_x > 0)
					{
						m_rect.left = j * 32 - m_rect.width; m_x *= -1;
					}
					else if (m_x < 0)
					{
						m_rect.left = j * 32 + 32;  m_x *= -1;
					}

				}
	}
}