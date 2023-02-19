#include "AnimationComponentTemplate.h"

AnimationComponentTemplate::AnimationComponentTemplate()
{
}

AnimationComponentTemplate::~AnimationComponentTemplate()
{
}

const bool AnimationComponentTemplate::loadFromFile(const std::string& file_name)
{
	std::ifstream input(file_name + "/list.dat", std::ios::in);
	if (input.is_open()) {
		std::string s;

		input >> s;
		while (s != "END") {
			this->animation_templates[s].loadFromFile(file_name + "/" + s);
		}
		input.close();

		return true;
	}
	return false;
}

std::map<std::string, AnimationTemplate>& AnimationComponentTemplate::getAnimationTemplates()
{
	return this->animation_templates;
}
