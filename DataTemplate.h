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

	const bool loadFromFile(const std::string& file_name);//�Դ����ַ���Ϊ�ļ�����ȡ����

	std::map<std::string, unsigned int>& getData();
};

#endif DATATEMPLATE_H