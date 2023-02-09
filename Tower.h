#ifndef TOWER_H
#define TOWER_H

#include<map>
#include<fstream>

#include"SFML/Graphics.hpp"

#include"TowerTemplate.h"

class Tower 
{
private:

	static std::map<std::string, TowerTemplate>tower_lib;
	
	sf::Vector2u pos;

public:

	Tower(std::string& name, sf::Vector2u& pos);
	~Tower();

	void setPos(const sf::Vector2u& pos);
	const sf::Vector2u& getPos();

};

#endif TOWER_H