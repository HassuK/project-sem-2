#pragma once
#include <SFML/Graphics.hpp>
#include <PLAYER.hpp>
#include <MAP.hpp>


int main()
{
	Globals TileMap = {

	   "B                                      B",
	   "B                                BBBBBBB",
	   "B                                0     B",
	   "B                                0     B",
	   "B                                0     B",
	   "B         0000                BBBB     B",
	   "B                                B     B",
	   "BBB                              B     B",
	   "B              BB                BB    B",
	   "B              BB                      B",
	   "B    B         BB          BB          B",
	   "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ",

	};
	const int W = 40;

	int stayflag = 0;

	sf::RenderWindow window(sf::VideoMode(600, 400), "Test!");

	sf::Texture t;
	if (!(t.loadFromFile("assets/fang.png"))) 
	{
		t.loadFromFile("../assets/fang.png");
	}
	

	sf::Texture tileSet;
	if(!(tileSet.loadFromFile("assets/blocks.png")))
	{
		tileSet.loadFromFile("../assets/blocks.png");
	}

	float currentFrame = 0;
	
	sf::Sprite tile(tileSet);
	my::PLAYER p(t, TileMap);

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

		if (p.getRectLeft() > 300 && p.getRectLeft() < 980)
		{
			p.setOffsetX(p.getRectLeft() - 300);
		}
		p.setOffsetY(p.getRectTop() - 200);

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
		window.display();
	}


	return 0;
}
