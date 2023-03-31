#ifndef FIELD_H
#define FIELD_H

#include"Tower.h"
#include"Entity.h"

#include"JudgeFunctions.h"

class Field
{
private:

	std::string file_name;
	sf::Vector2u size;

	std::vector<Tower*>towers;
	std::vector<Bullet*>bullets;
	std::vector<Entity*>entities;

	std::vector<sf::CircleShape>explosion_animation;
	std::vector<sf::CircleShape>explosion_animation_cache;

	std::vector<Barrier>barrier_map;

	void init();
	void initField();
	void initBarrierMap();

	void bulletTrigger();
	void bulletExplodeAnimation(Bullet* bullet);
	void dealDamage(Bullet* bullet);
	void recycleBullet();

	void collision();
	void collisionwithTowers();
	void collisionwithEntities();
	void collisionwithBullets();

	void updateExplosionSprite(sf::RectangleShape& display_shape);

public:
	Field(const std::string& file_name);

	~Field();

	void update(sf::RectangleShape& display_shape);
	void updateLogic();
	void updateSprite(sf::RectangleShape& display_shape);

	void render(sf::RenderTarget& target);
};

#endif