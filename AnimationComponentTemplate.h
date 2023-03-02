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

	const bool loadFromFile(const std::string& file_name);//�������list.dat�Ͷ�Ӧ�Ĺ�AnimationTemplate��ȡ���ļ��е��ļ���·��

	const bool isLoaded();

	std::map<std::string, AnimationTemplate>& getAnimationTemplates();

};

#endif