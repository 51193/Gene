#ifndef ENTITY_H
#define ENTITY_H

#include<iostream>

#include"Barrier.h"

#include"DataComponent.h"
#include"Bullet.h"

#include"JudgeFunctions.h"

struct EyeSight {
	sf::Vector2f point;
	float remain_length;
	float output_strength;
};

class Entity
{
private:

	static DataComponentTemplate data_component_template;

	DataComponent data_component;

	sf::Vector2f pos;
	int health_point;
	bool is_dead;

	sf::Vector2f velocity;

	std::map<std::string, sf::CircleShape>appearance;

	std::vector<EyeSight>eye_sight;

	void init();
	void initDataComponent();
	void initAppearance();

	void move();
	void friction();
	void eyesight(std::vector<Bullet*>& bullets, std::vector<Entity*>& entities, std::vector<Barrier>& barrier_map);

public:
	Entity(sf::Vector2u pos);
	~Entity();

	void assignVelocity(const sf::Vector2f& velocity);
	void setVelocity(const sf::Vector2f& velocity);

	void setPos(const sf::Vector2f& pos);

	const sf::Vector2f& getPos();
	const sf::Vector2f& getVelocity();
	DataComponent& getDataComponent();
	const bool isDead();
	const int getHealthPoint();

	void getHurt(unsigned int damage);

	void update(sf::Vector2u& size, sf::RectangleShape& display_shape, std::vector<Bullet*>& bullets, std::vector<Entity*>& entities, std::vector<Barrier>& barrier_map);
	void updateLogic(std::vector<Bullet*>& bullets, std::vector<Entity*>& entities, std::vector<Barrier>& barrier_map);
	void updateSprite(sf::Vector2u& size, sf::RectangleShape& display_shape);

	void render(sf::RenderTarget& target);
};

#endif