#ifndef PLAYER_H
#define PLAYER_H
#include"Entities.h"


class Player: public Entities
{
public:
	float DEGTORAD = 0.0174f;
	const int W = 1200;
	const int H = 800;
	bool thrust;
	Player();
	~Player();
	void update();
};

#endif

