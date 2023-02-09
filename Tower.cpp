#include "Tower.h"

Tower::Tower(std::string& name, sf::Vector2u& pos) :
	pos{ pos }
{
}

Tower::~Tower()
{
}

void Tower::setPos(const sf::Vector2u& pos)
{
	this->pos = pos;
}

const sf::Vector2u& Tower::getPos()
{
	return this->pos;
}