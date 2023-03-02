#ifndef TOWER_H
#define TOWER_H

#include<iostream>

#include"SFML/Graphics.hpp"

#include"TowerTemplate.h"
#include"DataComponent.h"
#include"AnimationComponent.h"

class Tower 
{
private:
	static std::map<std::string, TowerTemplate>tower_lib;

	sf::Sprite sprite;
	
	sf::Vector2u pos;

	DataComponent data_component;
	AnimationComponent animation_component;

public:

	Tower(const std::string& name, sf::Vector2u& pos);
	~Tower();

	void setPos(const sf::Vector2u& pos);
	const sf::Vector2u& getPos();

	void update(sf::Vector2u& size, sf::RectangleShape& display_shape, sf::RenderWindow& window);

	void render(sf::RenderTarget& target);

};

#endif TOWER_H