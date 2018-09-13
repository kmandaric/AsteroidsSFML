#ifndef Animation_H
#define Animation_H
#include<SFML\Graphics.hpp>

class Animation
{
public:
	float animSpeed;
	Animation();
	Animation(sf::Texture &t, int x, int y, int w, int h, int coF, float animSpeed);
	~Animation();
	float frame, speed;
	sf::Sprite animSprite;
	std::vector<sf::IntRect> framesofAnim;
	void update();
	bool isEnd();
};
#endif

