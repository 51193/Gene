#ifndef ANIMATIONCOMPONENTTEMPLATE_H
#define ANIMATIONCOMPONENTTEMPLATE_H

#include"AnimationTemplate.h"

class AnimationComponentTemplate
{
private:
	std::map<std::string, AnimationTemplate>animation_templates;

	bool is_loaded;

public:
	AnimationComponentTemplate();
	~AnimationComponentTemplate();

	const bool loadFromFile(const std::string& file_name);//传入包含list.dat和对应的供AnimationTemplate读取的文件夹的文件夹路径

	const bool isLoaded();

	std::map<std::string, AnimationTemplate>& getAnimationTemplates();

};

#endif