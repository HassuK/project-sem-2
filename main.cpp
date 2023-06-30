#pragma once
#include <SFML/Graphics.hpp>
#include <PLAYER.hpp>
#include <MAP.hpp>
#include <Enemy.h>
#include <iostream>


int main()
{
	Globals TileMap = {
		"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
		"0                                                                                                                                                    0",
		"0                P	                                                                  w                                                               0",
		"0                P  w                                  w                   w                                                                         0",
		"0  P             P                     w                                       kk                                                                    0",
		"0  P             P                                                            k  k    k    k                                                         0",
		"0  P             P     c                                                      k      kkk  kkk  w                                                     0",
		"0  P             P                                                      r     k       k    k                                                         0",
		"0                P                                                     rr     k  k                                                                   0",
		"0                P                                                    rrr      kk                                                                    0",
		"0               cP   kckck                                           rrrr                                                                            0",
		"0                P                      t0                           rrrrr                                                                           0",
		"0P               P                    00              t0          rrrrrr            G                                                                0",
		"0           d    P       d             00              00         rrrrrrr                                                                            0",
		"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
		"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
		"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",

	};
	const int W = 150;

	int stayflag = 0;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Test!");

	sf::Texture t;
	if (!(t.loadFromFile("assets/fang.png"))) 
	{
		t.loadFromFile("../assets/fang.png");
	}
	

	sf::Texture tileSet;
	sf::Texture enemyTexture;

	if(!(tileSet.loadFromFile("assets/blocks.png")))
	{
		tileSet.loadFromFile("../assets/blocks.png");
	}
	if (!(enemyTexture.loadFromFile("assets/mario.png")))
	{
		enemyTexture.loadFromFile("../assets/mario.png");
	}

	float currentFrame = 0;
	
	sf::Sprite tile(tileSet);
	my::PLAYER p(t, TileMap);

	other::ENEMY enemy(enemyTexture, TileMap, 24*16, 24*16);
//	enemy.set(enemyTexture, 3, 10);
	 

	sf::Clock clock;

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
				p.setY(-0.35);
				p.onGround = false; 
				stayflag = 1; 
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
		p.setOffsetY(p.getRectTop() - 200);
		enemy.setOffsetY(p.getRectTop() - 200);

		window.clear(sf::Color(200, 140, 255));


		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap.TileMap[i][j] == 'Z')
				{
					tile.setTextureRect((sf::IntRect(0, 0, 32, 32)));
				}

				if (TileMap.TileMap[i][j] == 'B')
				{
					tile.setTextureRect((sf::IntRect(0, 80, 32, 32)));
				}

				if (TileMap.TileMap[i][j] == '0')
				{
					tile.setTextureRect((sf::IntRect(240, 80, 32, 32)));
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


	return 0;
}
