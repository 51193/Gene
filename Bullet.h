#ifndef BULLET_H
#define BULLET_H

#include<math.h>

#include"SFML/Graphics.hpp"

#include"DataComponent.h"

class Bullet
{
private:
	DataComponent& data_component;

	sf::Vector2f position;

	sf::Vector2f velocity;

	sf::CircleShape pic;

	bool is_dead;

	unsigned int collision_timer;
	bool able_to_collision;

public:
	Bullet(sf::Vector2u& pos, DataComponent& data_component, const sf::Vector2f& target_point);
	~Bullet();

	DataComponent& getDataComponent();
	const sf::Vector2f& getPos();

	void setDead();
	const bool isDead();
	const bool abletoCollision();

	void setVelocity(const sf::Vector2f& velocity);
	const sf::Vector2f& getVelocity();

	void update(sf::Vector2u& size, sf::RectangleShape& display_shape);
	void updateLogic();
	void updateSprite(sf::Vector2u& size, sf::RectangleShape& display_shape);

	void render(sf::RenderTarget& target);
};

#endif