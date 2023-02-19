#ifndef ANIMATIONCOMPONENT
#define ANIMATIONCOMPONENT

#include"AnimationComponentTemplate.h"
#include"Animation.h"

class AnimationComponent
{
private:
	std::map<std::string, Animation*>animations;

	std::string last_animation_name;

public:
	AnimationComponent(sf::Sprite& sprite, AnimationComponentTemplate& animation_component_template);
	~AnimationComponent();

	void play(const std::string& name, const float& dt);
};

#endif