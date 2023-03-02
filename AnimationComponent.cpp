#include "AnimationComponent.h"

AnimationComponent::AnimationComponent()
	:is_loaded{ false }
{
}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations) {
		delete i.second;
	}
}

void AnimationComponent::loadFromTemplate(sf::Sprite& sprite, AnimationComponentTemplate& animation_component_template)
{
	std::map<std::string, AnimationTemplate>& animation_templates{ animation_component_template.getAnimationTemplates() };
	for (auto& i : animation_templates) {
		this->animations[i.first] = new Animation(sprite, i.second);
	}
	this->last_animation_name = this->animations.begin()->first;
	this->is_loaded = true;
}

const bool AnimationComponent::isLoaded()
{
	return is_loaded;
}

void AnimationComponent::play(const std::string& name)
{
	if (name == this->last_animation_name) {
		this->animations[name]->play();
	}
	else {
		this->animations[last_animation_name]->reset();
		this->animations[name]->play();
		this->last_animation_name = name;
	}
}
