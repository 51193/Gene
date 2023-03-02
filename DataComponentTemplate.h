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

	const bool loadFromFile(const std::string& file_name);//�Դ����ַ���Ϊ�ļ�����ȡ����

	const bool isLoaded();

	std::map<std::string, unsigned int>& getData();
};

#endif DATACOMPONENTTEMPLATE_H