#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	name = "Bullet";
}


Bullet::~Bullet()
{
}

void Bullet::update()
{
	dx = cos(angle*0.0174f) * 6;
	dy = sin(angle*0.0174f) * 6;

	x += dx;
	y += dy;
	if (x>1200 || x<0 || y>800 || y<0)
	{
		life = 0;
	}
	
}
