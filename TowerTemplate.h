#ifndef TOWERTEMPLATE_H
#define TOWERTEMPLATE_H

#include"DataComponentTemplate.h"
#include"AnimationComponentTemplate.h"

class TowerTemplate
{
private:
	DataComponentTemplate data_component_template;
	AnimationComponentTemplate animation_component_template;

	bool is_loaded;

	const bool loadDataFromFile(const std::string& file_name);//��ȡ����
	const bool loadAnimationFromFile(const std::string& file_name);//��ȡ����

public:
	TowerTemplate();
	~TowerTemplate();

	DataComponentTemplate& getDataComponentTemplate();
	AnimationComponentTemplate& getAnimationComponentTemplate();

	const bool loadFromFile(const std::string& file_name);

	const bool isLoaded();
};

#endif TOWERTEMPLATE_H