#include "Animation.h"

Animation::Animation(sf::Sprite& sprite, AnimationTemplate& animation_template)
	:sprite{ sprite }, texture_sheet{ animation_template.getTextureSheet() },
	timer{ 0.f }, current_frame{ 1 },
	time_each_frame{ animation_template.getTimeEachFrame() }, frame{ animation_template.getFrame() }, size{ animation_template.getSize() }
{
}

Animation::~Animation()
{
}

void Animation::reset()
{
	this->current_frame = 0;
	this->timer = 0.f;
}

void Animation::play(const float dt)
{
	this->sprite.setTexture(this->texture_sheet);

	this->timer += 1000.f * dt;
	if (this->timer > time_each_frame) {
		this->timer = 0.f;

		if (this->current_frame != frame) {
			this->current_frame++;
		}
		else {
			this->current_frame = 1;
		}
	}
	this->sprite.setTextureRect(sf::IntRect(this->size.x * (this->current_frame - 1), 0, this->size.x, this->size.y));
}