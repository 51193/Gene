#include "DataTemplate.h"

DataTemplate::DataTemplate()
{
}

DataTemplate::~DataTemplate()
{
}

const bool DataTemplate::loadFromFile(const std::string& file_name)
{
	std::ifstream input(file_name, std::ios::in);
	if (input.is_open()) {
		std::string s;
		unsigned int ui;

		input >> s;
		while (s != "END") {
			input >> ui;
			this->data[s] = ui;
			input >> s;
		}

		input.close();
		return true;
	}

	return false;
}

std::map<std::string, unsigned int>& DataTemplate::getData()
{
	return this->data;
}
