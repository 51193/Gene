#ifndef ANIMATIONTEMPLATE_H
#define ANIMATIONTEMPLATE_H

#include<string>
#include<fstream>

#include"SFML/Graphics.hpp"

class AnimationTemplate
{
private:
	sf::Texture texture_sheet;

	float time_each_frame;
	unsigned int frame;
	sf::Vector2i size;

	const bool loadConfigFromFile(const std::string& file_name);
	const bool loadTextureFromFile(const std::string& file_name);

public:
	AnimationTemplate();
	~AnimationTemplate();

	const bool loadFromFile(const std::string& file_name);//�������config.dat��texture.png���ļ�������������

	sf::Texture& getTextureSheet();
	const float& getTimeEachFrame();
	const unsigned int& getFrame();
	const sf::Vector2i& getSize();
};

#endif