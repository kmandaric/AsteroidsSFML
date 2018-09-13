#ifndef Entities_H
#define Entities_H
#include "Animation.h"
#include<SFML/Graphics.hpp>

class Entities:public Animation
{
public:
	Entities();
	virtual ~Entities();
	bool life;
	float dx, dy, x, y, rad, angle;
	std::string name;
	Animation ObAnim;
	void settings(Animation &a, float X, float Y, float Angle, int radius);
	virtual void update();
	void draw(sf::RenderWindow &ast);
	
};
#endif

