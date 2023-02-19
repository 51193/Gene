#ifndef DATATEMPLATE_H
#define DATATEMPLATE_H

#include<fstream>
#include<string>
#include<map>

class DataTemplate
{
private:
	std::map<std::string, unsigned int>data;

public:
	DataTemplate();
	~DataTemplate();

	const bool loadFromFile(const std::string& file_name);//以传入字符串为文件名读取数据

	std::map<std::string, unsigned int>& getData();
};

#endif DATATEMPLATE_H