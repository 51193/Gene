#ifndef ANIMATION_H
#define ANIMATION_H

#include"AnimationTemplate.h"

class Animation
{
private:

	sf::Sprite& sprite;
	sf::Texture& texture_sheet;

	float timer;
	const float& time_each_frame;

	unsigned int current_frame;
	const unsigned int& frame;

	const sf::Vector2i& size;

public:

	Animation(sf::Sprite& sprite, AnimationTemplate& animation_template);//��������������ã�ʹ�ø���ʱӦ��������ʧЧ
	~Animation();

	void reset();

	void play(const float dt);

};

#endif ANIMATION_H