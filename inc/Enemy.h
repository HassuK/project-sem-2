#pragma once
#include <PLAYER.hpp>
#include <MAP.hpp>
#include "logger.h"

namespace other {

	class ENEMY {

	private:
		float m_x, m_y;
		sf::FloatRect m_rect;
		sf::Sprite m_sprite;
		float currentFrame = 0;
		float m_offsetx = 0, m_offsety = 0;
		Globals* m_map;
		bool life;


	public:

		ENEMY() = default;
		

		ENEMY(sf::Texture& image, Globals& map, int x, int y);

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

		double getRectLeft() {
			return m_rect.left;
		}

		double getRectTop() {
			return m_rect.top;
		}

		void update(float time);

		void Collision();

		sf::FloatRect getRect()  {
			return m_rect;
		}

		bool getLife() {
			return life;
		}

		float getX() {
			return m_x;
		}

		float getY()  {
			return m_y;
		}

		void setX(float dx)  {
			m_x = dx;
		}

		void setY(float dy)  {
			m_y = dy;
		}

		void setLife(bool kill) {
			life = kill;
			logis::Logger::Info("You stomped Slimey! :(");
		}

		sf::Sprite getSprite() {
			return m_sprite;
		}

		~ENEMY() {};


	};



}