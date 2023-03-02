#include "DataComponentTemplate.h"

DataComponentTemplate::DataComponentTemplate()
	:is_loaded{ false }
{
}

DataComponentTemplate::~DataComponentTemplate()
{
}

const bool DataComponentTemplate::loadFromFile(const std::string& file_name)
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

		this->is_loaded = true;
		return true;
	}

	return false;
}

const bool DataComponentTemplate::isLoaded()
{
	return this->is_loaded;
}

std::map<std::string, unsigned int>& DataComponentTemplate::getData()
{
	return this->data;
}
