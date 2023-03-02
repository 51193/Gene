#ifndef ANIMATIONCOMPONENT
#define ANIMATIONCOMPONENT

#include"AnimationComponentTemplate.h"
#include"Animation.h"

class AnimationComponent
{
private:
	std::map<std::string, Animation*>animations;

	std::string last_animation_name;

	bool is_loaded;

public:
	AnimationComponent();
	~AnimationComponent();

	void loadFromTemplate(sf::Sprite& sprite, AnimationComponentTemplate& animation_component_template);

	const bool isLoaded();

	void play(const std::string& name);
};

#endif