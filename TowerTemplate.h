#ifndef TOWERTEMPLATE_H
#define TOWERTEMPLATE_H

#include"TowerData.h"

class TowerTemplate
{
private:
	
	TowerData tower_data;

public:
	TowerTemplate();
	~TowerTemplate();

	const bool LoadDataFromFile(const std::string& file_name);
	const bool LoadAnimationFromFile(const std::string& file_name);
};

#endif TOWERTEMPLATE_H