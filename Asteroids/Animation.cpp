#include "stdafx.h"
#include "Animation.h"


Animation::Animation(sf::Texture &t, int x, int y, int w, int h, int coF, float animSpeed)
{
	frame = 0;
	speed = animSpeed;
	

	for (int i = 0; i < coF; i++)
	{
		framesofAnim.push_back(sf::IntRect(x + i*w, y, w, h));
		animSprite.setTexture(t);
		animSprite.setOrigin(w / 2, h / 2);
		animSprite.setTextureRect(framesofAnim[0]);
	}
}

Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::update()
{
	frame += speed;
	int n = framesofAnim.size();
	if (frame >= n) frame -= n;
	if (n > 0) animSprite.setTextureRect(framesofAnim[int(frame)]);
}

bool Animation::isEnd()
{
	return frame + speed >= framesofAnim.size();
}

