#include "stdafx.h"
#include "Entities.h"
#include "Animation.h"
#include<SFML/Graphics.hpp>

Entities::Entities()
{
	life = true;
}
Entities::~Entities()
{
}

void Entities::settings(Animation &a, float X, float Y, float Angle, int radius)
{
	ObAnim = a;
	x = X;
	y = Y;
	angle = Angle;
	rad = radius;
}

void Entities::draw(sf::RenderWindow &ast)
{
	ObAnim.animSprite.setPosition(x, y);
	ObAnim.animSprite.setRotation(angle + 90);
	ast.draw(ObAnim.animSprite);

	sf::CircleShape circle(rad);
	circle.setFillColor(sf::Color(255, 0, 0, 170));
	circle.setPosition(x, y);
	circle.setOrigin(rad, rad);
}

void Entities::update()
{}

