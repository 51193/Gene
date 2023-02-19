#include "Field.h"

void Field::init()
{
	this->initField();
}

void Field::initField()
{
	std::ifstream input(file_name, std::ios::in);

	unsigned int temp_x{ 0 };
	unsigned int temp_y{ 0 };
	std::string name{};

	input >> temp_x >> temp_y;
	this->size = sf::Vector2u(temp_x, temp_y);

	input >> name;

	while (name != "END") {
		input >> temp_x >> temp_y;
		sf::Vector2u temp = sf::Vector2u(temp_x, temp_y);
		this->towers.push_back(new Tower(name, temp));
		input >> name;
	}

	input.close();
}

void Field::update()
{

}

void Field::render(sf::RenderTarget& target, const sf::FloatRect& field_size)
{

}

Field::Field(const std::string& file_name)
	:file_name{ file_name }
{
	this->init();
}

Field::~Field()
{
	for (auto& i : this->towers) {
		delete i;
	}
}
