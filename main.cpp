﻿#pragma once
#include <SFML/Graphics.hpp>
#include <PLAYER.hpp>
#include <MAP.hpp>
#include "logger.h"
#include "Enemy.h"
#include <iostream>


int main()
{
	logis::Logger::SetLogFlags(logis::Logger::GetLogFlags() | logis::LogFlags::File);
	logis::Logger::SetLogFilePath("log.txt");
	bool wrongtile = false;
	Globals TileMap = {

	   "     B                                      B                    ",
	   "     B                                BBBBBBB                    ",
	   "     B                                0     B                    ",
	   "     B                                0     B                    ",
	   "     B                                0     B                    ",
	   "     B         0000                BBBB     B                    ",
	   "     B                                B     B                    ",
	   "     BBB                              B     B                    ",
	   "     B              BB                BB    B                    ",
	   "     B              BB                      B                    ",
	   "     B    B         BB          BB          B                    ",
	   "ZZZZZDZZZZDZZZZZZZZZDDZZZZZZZZZZDDZZZZZZZZZZDZZZZZZZZZZZZZZZZZZZZ",
	   "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD",
	   "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD",
	   "DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD",
	};
	


	const int W = 65;

	try {
		for (int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				if ((i < 0) || (j < 0))
					throw std::range_error("Map out of range");


				if ((TileMap.TileMap[i][j] != 'B') && (TileMap.TileMap[i][j] != 'Z') && (TileMap.TileMap[i][j] != '0') && (TileMap.TileMap[i][j] != ' ') && (TileMap.TileMap[i][j] != 'D'))
					wrongtile = true;
			}
		}

		if (wrongtile == true) {
			throw std::invalid_argument("Wrong block.");
		}


	}
	catch (const std::invalid_argument& e) {
		logis::Logger::Error("Invalid argumernt. Unknown block detected.");
		return 0;
	}
	catch (const std::range_error& e) {
		logis::Logger::Error("Range error. Map out of range.");
		return 0;
	}





	int stayflag = 0;

	sf::RenderWindow window(sf::VideoMode(600, 400), "Let's play!");

	sf::Texture t;
	if (!(t.loadFromFile("assets/steve.png"))) 
	{
		t.loadFromFile("../assets/steve.png");
	}
	

	sf::Texture tileSet;
	if(!(tileSet.loadFromFile("assets/blocks.png")))
	{
		tileSet.loadFromFile("../assets/blocks.png");
	}
	sf::Texture enemyTexture;
	if (!(enemyTexture.loadFromFile("assets/slime.png")))
	{
		enemyTexture.loadFromFile("../assets/slime.png");
	}


	other::ENEMY enemy(enemyTexture, TileMap, 14 * 32, 10 * 32);
	float currentFrame = 0;
	
	sf::Sprite tile(tileSet);
	my::PLAYER p(t, TileMap);

	sf::Clock clock;


	


	logis::Logger::Info("Game started.");

	while (window.isOpen())
	{
		stayflag = 0;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 500;

		if (time > 20) time = 20;

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			p.setX(-0.1);
			stayflag = 1;
			p.f = true;
			p.direction = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			p.setX(0.1);
			stayflag = 1;
			p.f = true;
			p.direction = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (p.onGround) { 
				p.setY(-0.32);
				p.onGround = false; 
				stayflag = 1; 
				logis::Logger::Debug("Player pressed '^' being on the ground.");
				
			}
		}

		if (stayflag != 1)
		{
			p.f = false;
		}

		p.update(time);
		enemy.update(time);

		if (p.getRect().intersects(enemy.getRect()))
		{
			if (enemy.getLife()) {
				if (p.getY() > 0) {
					enemy.setX(0);
					p.setY(-0.2);
					enemy.setLife(false);
				}
				else p.getSprite().setColor(sf::Color::Blue);
			}
		}

		if (p.getRectLeft() > 200)
		{
			p.setOffsetX(p.getRectLeft() - 200);
			enemy.setOffsetX(p.getRectLeft() - 200);
		}
		p.setOffsetY(p.getRectTop() - 216);
		enemy.setOffsetY(p.getRectTop() - 216);


		window.clear(sf::Color(173, 216, 230));


		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap.TileMap[i][j] == 'Z')
				{
					tile.setTextureRect((sf::IntRect(0, 0, 32, 32)));
				}

				if (TileMap.TileMap[i][j] == 'B')
				{
					tile.setTextureRect((sf::IntRect(32, 0, 32, 32)));
				}

				if (TileMap.TileMap[i][j] == 'D')
				{
					tile.setTextureRect((sf::IntRect(96, 0, 32, 32)));
				}

				if (TileMap.TileMap[i][j] == '0')
				{
					tile.setTextureRect((sf::IntRect(64, 0, 32, 32)));
				}


				if (TileMap.TileMap[i][j] == ' ')
				{
					continue;
				}

				tile.setPosition(j * 32 - p.getOffetX(), i * 32 - p.getOffetY());
				window.draw(tile);
			}

		window.draw(p.getSprite());
		window.draw(enemy.getSprite());
		window.display();
	}

	logis::Logger::Info("Game closed.");
	return 0;
}
