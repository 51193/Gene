#ifndef DATACOMPONENT_H
#define DATACOMPONENT_H

#include"DataComponentTemplate.h"

class DataComponent
{
private:
	std::map<std::string, unsigned int> data;

	bool is_loaded;

public:
	DataComponent();

	void loadFromTemplate(DataComponentTemplate& data_template);

	const bool isLoaded();

	const unsigned int get(const std::string& data_name);
};

#endif