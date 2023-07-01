#pragma once
#include <PLAYER.hpp>
#include <MAP.hpp>
#include "logger.h"

namespace other {

	class ENEMY : public my::PLAYER{

	private:
		float m_currentFrame = 0;	
		bool life;


	public:

		ENEMY() = default;
		

		ENEMY(sf::Texture& image, Globals& map, int x, int y);

		void setOffsetX(float offsetx) override {
			m_offsetx = offsetx;
		}

		void setOffsetY(float offsety) override {
			m_offsety = offsety;
		}

		float getOffetX() override {
			return m_offsetx;
		}

		float getOffetY() override {
			return m_offsety;
		}

		double getRectLeft() override {
			return m_rect.left;
		}

		double getRectTop() override {
			return m_rect.top;
		}

		void update(float time) override;

		void Collision();

		sf::FloatRect getRect() override {
			return m_rect;
		}

		bool getLife() {
			return life;
		}

		float getX() override {
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
			logis::Logger::Info("You stomped Slimey! :(");
		}

		sf::Sprite getSprite() override {
			return m_sprite;
		}

	//	~ENEMY() {};


	};



}