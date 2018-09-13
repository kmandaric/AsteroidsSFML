#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	name = "Player";
}


Player::~Player()
{
}

void Player::update()
{
	if (thrust)
	{
		dx += cos(angle*DEGTORAD)*0.35f;
		dy += sin(angle*DEGTORAD)*0.35f;
	}
	else
	{
		dy *= 0.99f;
		dx *= 0.99f;
	}

	int maxSpeed = 8;
	float speed = sqrt(dx*dx + dy*dy);
	if (speed>maxSpeed)
	{
		dx *= maxSpeed / speed;
		dy *= maxSpeed / speed;
	}

	x += dx;
	y += dy;

	if (x>W) x = 0; if (x<0) x = W;
	if (y>H) y = 0; if (y<0) y = H;
}
