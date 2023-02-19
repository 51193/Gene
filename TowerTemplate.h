#ifndef TOWERTEMPLATE_H
#define TOWERTEMPLATE_H

#include<utility>

#include"DataTemplate.h"
#include"AnimationComponentTemplate.h"

class TowerTemplate
{
private:
	DataTemplate data_template;
	AnimationComponentTemplate animation_component_template;

	const bool loadDataFromFile(const std::string& file_name);//��ȡ����
	const bool loadAnimationFromFile(const std::string& file_name);//��ȡ����

public:
	TowerTemplate();
	~TowerTemplate();

	const bool loadFromFile(const std::string& file_name);
};

#endif TOWERTEMPLATE_H