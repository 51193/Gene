#ifndef TOWER_H
#define TOWER_H

#include<iostream>

#include"SFML/Graphics.hpp"

#include"Entity.h"
#include"Bullet.h"
#include"TowerTemplate.h"
#include"AnimationComponent.h"

class Tower 
{
private:
	static std::map<std::string, TowerTemplate>tower_lib;

	sf::Sprite sprite;

	sf::CircleShape range;
	sf::RectangleShape outline;
	
	sf::Vector2u pos;

	DataComponent data_component;
	AnimationComponent animation_component;

	unsigned int timer;
	bool is_ready;

	void shoot(std::vector<Entity*>& entities, std::vector<Bullet*>& bullets);

public:

	Tower(const std::string& name, sf::Vector2u& pos);
	~Tower();

	void setPos(const sf::Vector2u& pos);
	const sf::Vector2u& getPos();
	DataComponent& getDataComponent();

	const sf::Sprite getSprite();

	const bool isReady();

	void update(sf::Vector2u& size, sf::RectangleShape& display_shape, std::vector<Entity*>& entities, std::vector<Bullet*>& bullets);
	void updateLogic(std::vector<Entity*>& entities, std::vector<Bullet*>& bullets);
	void updateSprite(sf::Vector2u& size, sf::RectangleShape& display_shape);

	void render(sf::RenderTarget& target);

};

#endif TOWER_H