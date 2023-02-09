#ifndef FIELD_H
#define FIELD_H

#include<iostream>

#include "Tower.h"

class Field
{
private:

	std::string file_name;
	sf::Vector2u size;

	std::vector<Tower*>towers;

	void init();
	void initField();


public:
	Field(const std::string& file_name);

	~Field();

	void update();
	void render(sf::RenderTarget& target, const sf::FloatRect& field_size);
};

#endif