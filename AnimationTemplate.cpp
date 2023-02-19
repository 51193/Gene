#include "AnimationTemplate.h"

AnimationTemplate::AnimationTemplate()
{
}

AnimationTemplate::~AnimationTemplate()
{
}

const bool AnimationTemplate::loadFromFile(const std::string& file_name)
{
	if (
		this->loadConfigFromFile(file_name + "/config.dat") &&
		this->loadTextureFromFile(file_name + "/texture.png")
		)
		return true;
	return false;
}

sf::Texture& AnimationTemplate::getTextureSheet()
{
	return this->texture_sheet;
}

const float& AnimationTemplate::getTimeEachFrame()
{
	return this->time_each_frame;
}

const unsigned int& AnimationTemplate::getFrame()
{
	return this->frame;
}

const sf::Vector2i& AnimationTemplate::getSize()
{
	return this->size;
}

const bool AnimationTemplate::loadConfigFromFile(const std::string& file_name)
{
	std::ifstream input(file_name, std::ios::in);
	if (input.is_open()) {
		input >> this->size.x >> this->size.y >> this->frame >> this->time_each_frame;
		input.close();
		return true;
	}
	return false;
}

const bool AnimationTemplate::loadTextureFromFile(const std::string& file_name)
{
	if (this->texture_sheet.loadFromFile(file_name))return true;
	return false;
}
