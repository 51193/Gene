#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, AnimationComponentTemplate& animation_component_template)
{
	std::map<std::string, AnimationTemplate>& animation_templates{ animation_component_template.getAnimationTemplates() };
	for (auto& i : animation_templates) {
		this->animations[i.first] = new Animation(sprite, i.second);
	}
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations) {
		delete i.second;
	}
}

void AnimationComponent::play(const std::string& name, const float& dt)
{
	if (name == this->last_animation_name) {
		this->animations[name]->play(dt);
	}
	else {
		this->animations[last_animation_name]->reset();
		this->animations[name]->play(dt);
		this->last_animation_name = name;
	}
}
