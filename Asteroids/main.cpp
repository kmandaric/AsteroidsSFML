#include "stdafx.h"
#include <time.h>
#include "Animation.h"
#include "Entities.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Player.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include<list>


const int W = 1200;
const int H = 800;
float DEGTORAD = 0.0174f;

//bool isCollide(Entities *a, Entities *b) {
//	return(a->ObAnim.animSprite.getGlobalBounds().intersects(b->ObAnim.animSprite.getGlobalBounds()));
//}

//ALL ASTEROIDS EXPLODE ON APP START

bool isCollide(Entities *a, Entities *b)
{
	return (b->x - a->x)*(b->x - a->x) +(b->y - a->y)*(b->y - a->y)<(a->rad + b->rad)*(a->rad + b->rad);
}

// MORE DETAILED COLLISION


int main()
{
	sf::RenderWindow ast(sf::VideoMode(W,H), "Asteroids!");
	ast.setFramerateLimit(60);
	
	sf::Texture	sp,bg,rock,rockS,bul,exp1,exp2;
	sp.loadFromFile("images/spaceship.png");
	bg.loadFromFile("images/background.jpg");
	rock.loadFromFile("images/rock.png");
	rockS.loadFromFile("images/rock_small.png");
	bul.loadFromFile("images/fire_blue.png");
	exp1.loadFromFile("images/explosions/type_C.png");
	exp2.loadFromFile("images/explosions/type_B.png");

	sf::Sprite sBackground(bg);

	Animation sPlayer(sp, 40, 0, 40, 40, 1, 0);
	Animation sPlayer2(sp, 40, 40, 40, 40, 1, 0);
	Animation sPlayerExp(exp2, 0, 0, 192, 192, 64, 0.5);
	Animation sRock(rock, 0, 0, 64, 64, 16, 0.15f);
	Animation sRockSmall(rockS, 0, 0, 64, 64, 16, 0.2);
	Animation sBullet(bul, 0, 0, 32, 64, 16, 0.8f);
	Animation sExplosion(exp1, 0, 0, 256, 256, 48, 0.5);


	std::list<Entities*> GameObjects;

	Player *P = new Player();
	P->settings(sPlayer, 600, 400, 0, 25);
	P->dx = 0;
	P->dy = 0;
	GameObjects.push_back(P);

	for (int i = 0; i < 15; i++)
	{
		Asteroid *a = new Asteroid();
		a->settings(sRock, rand()%W, rand()%H, rand() % 360, 10);
		GameObjects.push_back(a);
	}


	while (ast.isOpen())
	{
		sf::Event event;
		while (ast.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				ast.close();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				ast.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					Bullet *b = new Bullet();
					b->settings(sBullet, P->x, P->y, P->angle, 10);
					GameObjects.push_back(b);
				}
			}
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) P->angle -= 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) P->angle += 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) P->thrust=true;
		else P-> thrust = false;
		


		for (auto i=GameObjects.begin();i!=GameObjects.end();)
		{
			Entities *e = *i;
			e->update();
			e->ObAnim.update();

			if (e->life == false)
			{
				i = GameObjects.erase(i);
				delete e;
			}
			else i++;
		}


		for (auto a : GameObjects)
			for (auto b : GameObjects)
			{
				if (a->name == "Asteroid" && b->name == "Bullet")
					if (isCollide(a, b))
					{
						a->life = false;
						b->life = false;

						Entities *e = new Entities();
						e->settings(sExplosion, a->x, a->y, 0,1);
						e->name = "Explosion";
						GameObjects.push_back(e);

						for (int i = 0; i < 2; i++)
						{
							if (a->rad == 15) continue;
							Entities *e = new Asteroid();
							e->settings(sRockSmall, a->x, a->y,0,15);
							GameObjects.push_back(e);
						}

					}


				if (a->name == "Player" && b->name == "Asteroid")
					if (isCollide(a, b))
					{
						b->life = false;

						Entities *e = new Entities();
						e->settings(sPlayerExp, a->x, a->y, rand() % 360, 15);
						e->name = "Explosion";
						GameObjects.push_back(e);

						P->settings(sPlayer, rand() % W, rand() % H, 0, 20);
						P->dx = 0;
						P->dy = 0;
					}
					
					
			}


		if (P->thrust)  P->ObAnim = sPlayer2;
		else   P->ObAnim = sPlayer;
		
		for (auto e : GameObjects)
			if (e->name == "Explosion")
				if (e->ObAnim.isEnd()) e->life = 0;

		if (rand() % 150 == 0)
		{
			Asteroid *a = new Asteroid();
			a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
			GameObjects.push_back(a);
		}
				
		
	
		ast.draw(sBackground);
		for (auto i : GameObjects)
			i->draw(ast);
		ast.display();
	}

    return 0;
}

