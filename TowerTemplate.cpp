#include "TowerTemplate.h"

TowerTemplate::TowerTemplate()
{
}

TowerTemplate::~TowerTemplate()
{
}

const bool TowerTemplate::loadFromFile(const std::string& file_name)
{
	if (
		this->loadDataFromFile(file_name + "/data.dat") &&
		this->loadAnimationFromFile(file_name + "/animation")
		) {
		return true;
	}
	return false;
}

const bool TowerTemplate::loadDataFromFile(const std::string& file_name)
{
	return this->data_template.loadFromFile(file_name);
}

const bool TowerTemplate::loadAnimationFromFile(const std::string& file_name)
{
	return this->animation_component_template.loadFromFile(file_name);
}