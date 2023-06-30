#pragma once
#include <PLAYER.hpp>
#include <MAP.hpp>

namespace other {

	class ENEMY : public my::PLAYER {

	protected:
		bool life;


	public:

		ENEMY(sf::Texture& image, Globals& map) {
			m_sprite.setTexture(image);
			m_rect = sf::FloatRect(0, 0, 16, 16);
			m_x = m_y = 0.1;
			currentFrame = 0;
			m_map = &map;
			life = true;
		}

		void set(sf::Texture& image,int x, int y) {
			m_sprite.setTexture(image);
			m_rect = sf::FloatRect(x, y, 16, 16);
			m_x = m_y = 0.1;
			currentFrame = 0;
			life = true;
		}

		void update(float time) override
		{
			m_rect.left += m_x * time;

			Collision();

			currentFrame += time * 0.005;
			if (currentFrame > 2) currentFrame -= 2;

			m_sprite.setTextureRect(sf::IntRect(18 * int(currentFrame), 0, 16, 16));
			if (!life) m_sprite.setTextureRect(sf::IntRect(58, 0, 16, 16));


			m_sprite.setPosition(m_rect.left - m_offsetx, m_rect.top - m_offsety);

		}


		void Collision() 
		{

			for (int i = m_rect.top / 32; i < (m_rect.top + m_rect.height) / 32; i++)
				for (int j = m_rect.left / 32; j < (m_rect.left + m_rect.width) / 32; j++)
					if ((m_map->TileMap[i][j] == 'P') || (m_map->TileMap[i][j] == '0'))
					{
						if (m_x > 0)
						{
							m_rect.left = j * 32  - m_rect.width; m_x *= -1;
						}
						else if (m_x < 0)
						{
							m_rect.left = j * 32 + 32;  m_x *= -1;
						}

					}
		}

		sf::FloatRect getRect() override {
			return m_rect;
		}

		bool getLife() {
			return life;
		}

		float getX() override{
			return m_x;
		}

		float getY() override {
			return m_y;
		}

		void setX(float dx) override {
			m_x = dx;
		}

		void setY(float dy) override {
			m_y = dy;
		}

		void setLife(bool kill) {
			life = kill;
		}
	};






}