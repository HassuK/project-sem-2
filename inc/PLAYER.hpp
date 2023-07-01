#pragma once
#include <SFML/Graphics.hpp>
#include <MAP.hpp>




namespace my {
	class PLAYER {

	protected:
		float m_x, m_y;
		sf::FloatRect m_rect;
		sf::Sprite m_sprite;
		float m_offsetx = 0, m_offsety = 0;
		Globals* m_map;

	public:

		bool onGround;
		float currentFrame;
		bool f, direction;


		PLAYER() = default;
		PLAYER(sf::Texture& image, Globals& map);

		virtual	void setOffsetX(float offsetx) {
			m_offsetx = offsetx;
		}

		virtual	void setOffsetY(float offsety) {
			m_offsety = offsety;
		}

		virtual	float getOffetX() {
			return m_offsetx;
		}

		virtual	float getOffetY() {
			return m_offsety;
		}

		virtual	void setX(float dx) {
			m_x = dx;
		}

		virtual	void setY(float dy) {
			m_y = dy;
		}

		virtual	void update(float time);


		virtual	double getRectLeft() {
			return m_rect.left;
		}

		virtual	double getRectTop() {
			return m_rect.top;
		}

		virtual	float getX() {
			return m_x;
		}

		virtual	float getY() {
			return m_y;
		}

		void Collision(int dir);

		virtual	sf::Sprite getSprite() {
			return m_sprite;
		}

		virtual	sf::FloatRect getRect() {
			return m_rect;
		}


		virtual ~PLAYER() {};
	};


}