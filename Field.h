#ifndef FIELD_H
#define FIELD_H

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

	void update(sf::RectangleShape& display_shape, sf::RenderWindow& window);
	void render(sf::RenderTarget& target);
};

#endif