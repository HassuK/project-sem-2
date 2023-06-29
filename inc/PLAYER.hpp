#pragma once
#include <SFML/Graphics.hpp>
#include <MAP.hpp>



namespace my {
	class PLAYER {

	private:
		float m_x, m_y;
		sf::FloatRect m_rect;
		sf::Sprite m_sprite;
		float m_offsetx = 0, m_offsety = 0;
		Globals* m_map;

	public:

	
		bool onGround;
		float currentFrame;
		bool f, direction;

	

		PLAYER(sf::Texture& image, Globals& map);
		
		void setOffsetX(float offsetx) {
			m_offsetx = offsetx;
		}

		void setOffsetY(float offsety) {
			m_offsety = offsety;
		}

		float getOffetX() {
			return m_offsetx;
		}

		float getOffetY() {
			return m_offsety;
		}

		void setX(float dx) {
			m_x = dx;
		}

		void setY(float dy) {
			m_y = dy;
		}

		void update(float time);
		

		double getRectLeft() {
			return m_rect.left;
		}

		double getRectTop() {
			return m_rect.top;
		}

		void Collision(int dir);

		sf::Sprite getSprite() {
			return m_sprite;
		}
		
		~PLAYER() {};
	};
	
}