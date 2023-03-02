#include "TowerTemplate.h"

TowerTemplate::TowerTemplate()
	:is_loaded{ false }
{
}

TowerTemplate::~TowerTemplate()
{
}

DataComponentTemplate& TowerTemplate::getDataComponentTemplate()
{
	return this->data_component_template;
}

AnimationComponentTemplate& TowerTemplate::getAnimationComponentTemplate()
{
	return this->animation_component_template;
}

const bool TowerTemplate::loadFromFile(const std::string& file_name)
{
	if (
		this->loadDataFromFile(file_name + "\\data.dat") &&
		this->loadAnimationFromFile(file_name + "\\animation")
		) {
		this->is_loaded = true;
		return true;
	}
	return false;
}

const bool TowerTemplate::isLoaded()
{
	return this->is_loaded;
}

const bool TowerTemplate::loadDataFromFile(const std::string& file_name)
{
	return this->data_component_template.loadFromFile(file_name);
}

const bool TowerTemplate::loadAnimationFromFile(const std::string& file_name)
{
	return this->animation_component_template.loadFromFile(file_name);
}