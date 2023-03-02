#include "AnimationComponentTemplate.h"

AnimationComponentTemplate::AnimationComponentTemplate()
	:is_loaded{ false }
{
}

AnimationComponentTemplate::~AnimationComponentTemplate()
{
}

const bool AnimationComponentTemplate::loadFromFile(const std::string& file_name)
{
	std::ifstream input(file_name + "\\list.dat", std::ios::in);
	if (input.is_open()) {
		std::string s;

		input >> s;
		while (s != "END") {
			this->animation_templates[s].loadFromFile(file_name + "\\" + s);
			input >> s;
		}
		input.close();

		this->is_loaded = true;

		return true;
	}
	return false;
}

const bool AnimationComponentTemplate::isLoaded()
{
	return this->is_loaded;
}

std::map<std::string, AnimationTemplate>& AnimationComponentTemplate::getAnimationTemplates()
{
	return this->animation_templates;
}
