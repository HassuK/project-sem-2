#pragma once
#include <SFML/Graphics.hpp>
#include <MAP.hpp>
#include <PLAYER.hpp>
#include "logger.h"



namespace my {


	PLAYER::PLAYER(sf::Texture& image, Globals& map)
	{
		m_sprite.setTexture(image);
		m_rect = sf::FloatRect(7 * 32, 9 * 32, 64, 64);
		m_x = m_y = 0.1;
		currentFrame = 0;
		m_map = &map;
	}


	void PLAYER::update(float time)
	{
		m_rect.left += m_x * time;
		Collision(0);
		if (!onGround)
		{
			m_y = m_y + 0.0005 * time;
		}
		m_rect.top += m_y * time;
		onGround = false;
		Collision(1);

		if (f)
		{
			currentFrame += 0.005 * time;

			if (currentFrame > 6) {
				currentFrame -= 6;
			}
			if (m_x > 0) {
				m_sprite.setTextureRect(sf::IntRect(64 * static_cast<int>(currentFrame), 64, 64, 64));
			}

			if (m_x < 0) {
				m_sprite.setTextureRect(sf::IntRect(64 * static_cast<int>(currentFrame) + 64, 64, -64, 64));
			}
			f = false;
		}
		else
		{
			currentFrame += 0.0025 * time;
			if (currentFrame > 3) {
				currentFrame -= 3;
			}
			if (direction) {
				m_sprite.setTextureRect(sf::IntRect(64 * static_cast<int>(currentFrame), 0, 64, 64));
			}
			if (!direction) {
				m_sprite.setTextureRect(sf::IntRect(64 * static_cast<int>(currentFrame) + 64, 0, -64, 64));
			}
		}

		m_sprite.setPosition(m_rect.left - m_offsetx, m_rect.top - m_offsety);

		m_x = 0;
	}



	void PLAYER::Collision(int dir)
	{
		for (int i = m_rect.top / 32; i < (m_rect.top + m_rect.height) / 32; i++)
			for (int j = m_rect.left / 32; j < (m_rect.left + m_rect.width) / 32; j++)
			{
				if ((m_map->TileMap[i][j] == 'B') || (m_map->TileMap[i][j] == 'Z'))
				{
					if ((m_x > 0) && (dir == 0)) {
						m_rect.left = j * 32 - m_rect.width;
					}
					if ((m_x < 0) && (dir == 0)) {
						m_rect.left = j * 32 + 32;
					}
					if ((m_y > 0) && (dir == 1)) {
						m_rect.top = i * 32 - m_rect.height;
						m_y = 0;
						onGround = true;
					}
					if ((m_y < 0) && (dir == 1)) {
						m_rect.top = i * 32 + 32;
						m_y = 0;
					}
				}

				if (m_map->TileMap[i][j] == '0')
				{
					m_map->TileMap[i][j] = ' ';
					logis::Logger::Info("Apple collected.");
				}

			}
	}



}