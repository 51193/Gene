#ifndef ANIMATIONCOMPONENTTEMPLATE_H
#define ANIMATIONCOMPONENTTEMPLATE_H

#include"AnimationTemplate.h"

class AnimationComponentTemplate
{
private:
	std::map<std::string, AnimationTemplate>animation_templates;

public:
	AnimationComponentTemplate();
	~AnimationComponentTemplate();

	const bool loadFromFile(const std::string& file_name);//传入包含list.dat和对应的供AnimationTemplate读取的文件夹的文件夹路径

	std::map<std::string, AnimationTemplate>& getAnimationTemplates();

};

#endif