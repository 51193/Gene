#ifndef DATACOMPONENT_H
#define DATACOMPONENT_H

#include"DataTemplate.h"

class DataComponent
{
private:
	std::map<std::string, unsigned int>& data;

public:
	DataComponent(DataTemplate& data_template);

	const unsigned int get(const std::string& data_name);
};

#endif