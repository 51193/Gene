#ifndef DATACOMPONENTTEMPLATE_H
#define DATACOMPONENTTEMPLATE_H

#include<fstream>
#include<string>
#include<map>

class DataComponentTemplate
{
private:
	std::map<std::string, unsigned int>data;

	bool is_loaded;

public:
	DataComponentTemplate();
	~DataComponentTemplate();

	const bool loadFromFile(const std::string& file_name);//以传入字符串为文件名读取数据

	const bool isLoaded();

	std::map<std::string, unsigned int>& getData();
};

#endif DATACOMPONENTTEMPLATE_H