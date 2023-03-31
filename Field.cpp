#include "Field.h"

void Field::init()
{
	this->initField();
	this->initBarrierMap();
}

void Field::initField()
{
	std::ifstream input(file_name, std::ios::in);

	if (input.is_open()) {
		unsigned int temp_x{ 0 };
		unsigned int temp_y{ 0 };
		std::string name{};

		input >> temp_x >> temp_y;
		this->size = sf::Vector2u(temp_x, temp_y);

		input >> name;

		while (name != "END") {
			input >> temp_x >> temp_y;
			sf::Vector2u temp = sf::Vector2u(temp_x, temp_y);
			if (name != "entity") {
				this->towers.push_back(new Tower(name, temp));
			}
			else {
				this->entities.push_back(new Entity(temp));
			}
			input >> name;
		}
		input.close();
	}
}

void Field::initBarrierMap()
{
	Barrier temp;
	temp.center = sf::Vector2f((float)this->size.x / 2.f, -100.f);
	temp.size = sf::Vector2f((float)this->size.x, 200.f);
	this->barrier_map.push_back(temp);

	temp.center = sf::Vector2f(-100.f, (float)this->size.y / 2.f);
	temp.size = sf::Vector2f(200.f, (float)this->size.y);
	this->barrier_map.push_back(temp);

	temp.center = sf::Vector2f((float)this->size.x + 100.f, (float)this->size.y / 2.f);
	temp.size = sf::Vector2f(200.f, (float)this->size.y);
	this->barrier_map.push_back(temp);

	temp.center = sf::Vector2f((float)this->size.x / 2.f, (float)this->size.y + 100.f);
	temp.size = sf::Vector2f((float)this->size.x, 200.f);
	this->barrier_map.push_back(temp);

	for (auto& i : this->towers) {
		Barrier temp;
		temp.center = sf::Vector2f((float)i->getPos().x, (float)i->getPos().y);
		temp.size = sf::Vector2f((float)i->getDataComponent().get("SIZE_X"), (float)i->getDataComponent().get("SIZE_Y"));
		this->barrier_map.push_back(temp);
	}
}

void Field::bulletTrigger()
{
	this->explosion_animation_cache.clear();

	for (auto& i : this->bullets) {

		for (auto& j : this->entities) {
			if (
				!i->isDead() &&
				!j->isDead() &&
				JudgeFunctions::CircleandCircle(i->getPos(), (float)i->getDataComponent().get("BULLET_RADIUS"), j->getPos(), (float)j->getDataComponent().get("RADIUS"))
				)
			{
				this->bulletExplodeAnimation(i);

				this->dealDamage(i);

				break;
			}
		}
	}

	for (size_t i{ 0 }; i < this->bullets.size(); i++) {
		for (size_t j{ i + 1 }; j < this->bullets.size(); j++) {
			if (!this->bullets[i]->isDead() &&
				!this->bullets[j]->isDead() &&
				JudgeFunctions::CircleandCircle(this->bullets[i]->getPos(), (float)this->bullets[i]->getDataComponent().get("BULLET_RADIUS"), this->bullets[j]->getPos(), (float)this->bullets[j]->getDataComponent().get("BULLET_RADIUS"))
				)
			{
				this->bulletExplodeAnimation(this->bullets[i]);
				this->bulletExplodeAnimation(this->bullets[j]);

				this->dealDamage(this->bullets[i]);
				this->dealDamage(this->bullets[j]);

				break;
			}
		}
	}
}

void Field::bulletExplodeAnimation(Bullet* bullet)
{
	this->explosion_animation_cache.push_back(sf::CircleShape());
	this->explosion_animation_cache.rbegin()->setRadius(100.f);
	this->explosion_animation_cache.rbegin()->setPosition(
		(bullet->getPos().x - (float)bullet->getDataComponent().get("BULLET_EXPLODE_RADIUS")) / (float)this->size.x,
		(bullet->getPos().y - (float)bullet->getDataComponent().get("BULLET_EXPLODE_RADIUS")) / (float)this->size.y
	);
	this->explosion_animation_cache.rbegin()->setScale(
		(float)bullet->getDataComponent().get("BULLET_EXPLODE_RADIUS") * 2.f / (float)this->size.x / this->explosion_animation_cache.rbegin()->getLocalBounds().width,
		(float)bullet->getDataComponent().get("BULLET_EXPLODE_RADIUS") * 2.f / (float)this->size.y / this->explosion_animation_cache.rbegin()->getLocalBounds().height
	);
	this->explosion_animation_cache.rbegin()->setFillColor(sf::Color::Red);
}

void Field::dealDamage(Bullet* bullet)
{
	for (auto& i : this->entities) {
		if (
			!i->isDead() &&
			JudgeFunctions::CircleandCircle(bullet->getPos(), (float)bullet->getDataComponent().get("BULLET_RADIUS"), i->getPos(), (float)i->getDataComponent().get("RADIUS"))
			)

		{
			i->getHurt(bullet->getDataComponent().get("BULLET_DAMAGE"));

			if (!i->isDead()) {
				sf::Vector2f dir{ i->getPos() - bullet->getPos() };
				float a{ bullet->getDataComponent().get("BULLET_ASSIGN_VELOCITY") / JudgeFunctions::PointDistance(dir,sf::Vector2f(0.f,0.f)) };
				i->assignVelocity(dir * a);
			}
		}
	}

	//下面是一段可以让炮弹连锁爆炸的代码，会导致stack overflow，不知道为什么，也不是很重要，就先放这不管了
	//for (auto& i : this->bullets) {
	//	if (
	//		i!=bullet&&
	//		!i->isDead() &&
	//		JudgeFunctions::CircleandCircle(bullet->getPos(), (float)bullet->getDataComponent().get("BULLET_RADIUS"), i->getPos(), (float)i->getDataComponent().get("RADIUS"))
	//		)

	//	{
	//		this->bulletExplodeAnimation(i);
	//		this->dealDamage(i);
	//	}
	//}

	bullet->setDead();
}

void Field::recycleBullet()
{
	for (size_t i{ 0 }; i < this->bullets.size(); i++) {
		if (this->bullets[i]->isDead() || this->bullets[i]->getPos().x > (float)this->size.x * 1.2 || this->bullets[i]->getPos().y > (float)this->size.y * 1.2) {
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin() + i);
		}
	}
}

void Field::collision()
{
	this->collisionwithEntities();
	this->collisionwithTowers();
	this->collisionwithBullets();
}

void Field::collisionwithTowers()
{
	//以后写代码，所有拥有物理效果的类都应该从同一个类里派生出来，比现在这么写方便
	for (auto& i : this->barrier_map) {

		for (auto& j : this->bullets) {
			if (j->abletoCollision()) {
				if (JudgeFunctions::CircleandRectangle(i.center, i.size, j->getPos(), (float)j->getDataComponent().get("BULLET_RADIUS"))) {
					if (JudgeFunctions::CircleandPoint(j->getPos(), (float)j->getDataComponent().get("BULLET_RADIUS"), sf::Vector2f(i.center.x - i.size.x / 2.f, i.center.y - i.size.y / 2.f)) ||
						JudgeFunctions::CircleandPoint(j->getPos(), (float)j->getDataComponent().get("BULLET_RADIUS"), sf::Vector2f(i.center.x + i.size.x / 2.f, i.center.y - i.size.y / 2.f)) ||
						JudgeFunctions::CircleandPoint(j->getPos(), (float)j->getDataComponent().get("BULLET_RADIUS"), sf::Vector2f(i.center.x - i.size.x / 2.f, i.center.y + i.size.y / 2.f)) ||
						JudgeFunctions::CircleandPoint(j->getPos(), (float)j->getDataComponent().get("BULLET_RADIUS"), sf::Vector2f(i.center.x + i.size.x / 2.f, i.center.y + i.size.y / 2.f))
						) {
						j->setVelocity(sf::Vector2f(0.f - j->getVelocity().x, 0.f - j->getVelocity().y));
					}
					else {
						if (JudgeFunctions::CircleandLine(
								j->getPos(), (float)j->getDataComponent().get("BULLET_RADIUS"),
								sf::Vector2f(i.center.x - i.size.x / 2.f, i.center.y - i.size.y / 2.f),
								sf::Vector2f(i.center.x + i.size.x / 2.f, i.center.y - i.size.y / 2.f)) ||
							JudgeFunctions::CircleandLine(
								j->getPos(), (float)j->getDataComponent().get("BULLET_RADIUS"),
								sf::Vector2f(i.center.x - i.size.x / 2.f, i.center.y + i.size.y / 2.f),
								sf::Vector2f(i.center.x + i.size.x / 2.f, i.center.y + i.size.y / 2.f))) {

							j->setVelocity(sf::Vector2f(j->getVelocity().x, j->getVelocity().y * (-1)));
						}
						else {
							j->setVelocity(sf::Vector2f(j->getVelocity().x * (-1), j->getVelocity().y));
						}
					}

				}
			}
		}

		for (auto& j : this->entities) {
			if (JudgeFunctions::CircleandRectangle(i.center, i.size, j->getPos(), (float)j->getDataComponent().get("RADIUS"))) {
				if (JudgeFunctions::CircleandPoint(j->getPos(), (float)j->getDataComponent().get("RADIUS"), sf::Vector2f(i.center.x - i.size.x / 2.f, i.center.y - i.size.y / 2.f)) ||
					JudgeFunctions::CircleandPoint(j->getPos(), (float)j->getDataComponent().get("RADIUS"), sf::Vector2f(i.center.x + i.size.x / 2.f, i.center.y - i.size.y / 2.f)) ||
					JudgeFunctions::CircleandPoint(j->getPos(), (float)j->getDataComponent().get("RADIUS"), sf::Vector2f(i.center.x - i.size.x / 2.f, i.center.y + i.size.y / 2.f)) ||
					JudgeFunctions::CircleandPoint(j->getPos(), (float)j->getDataComponent().get("RADIUS"), sf::Vector2f(i.center.x + i.size.x / 2.f, i.center.y + i.size.y / 2.f))
					) {
					j->setVelocity(sf::Vector2f(0.f - j->getVelocity().x, 0.f - j->getVelocity().y));
				}
				else {
					if (JudgeFunctions::CircleandLine(
							j->getPos(), (float)j->getDataComponent().get("RADIUS"),
							sf::Vector2f(i.center.x - i.size.x / 2.f, i.center.y - i.size.y / 2.f),
							sf::Vector2f(i.center.x + i.size.x / 2.f, i.center.y - i.size.y / 2.f)) ||
						JudgeFunctions::CircleandLine(
							j->getPos(), (float)j->getDataComponent().get("RADIUS"),
							sf::Vector2f(i.center.x - i.size.x / 2.f, i.center.y + i.size.y / 2.f),
							sf::Vector2f(i.center.x + i.size.x / 2.f, i.center.y + i.size.y / 2.f))) {

						j->setVelocity(sf::Vector2f(j->getVelocity().x, j->getVelocity().y * (-1)));
					}
					else {
						j->setVelocity(sf::Vector2f(j->getVelocity().x * (-1), j->getVelocity().y));
					}
				}

			}
		}
	}
}

void Field::collisionwithEntities()
{
	for (size_t i{ 0 }; i < this->entities.size(); i++) {
		for (size_t j{ i + 1 }; j < this->entities.size(); j++) {
			if (JudgeFunctions::CircleandCircle(this->entities[i]->getPos(), (float)this->entities[i]->getDataComponent().get("RADIUS"), this->entities[j]->getPos(), (float)this->entities[j]->getDataComponent().get("RADIUS"))) {
				sf::Vector2f temp1{ this->entities[i]->getVelocity() };
				sf::Vector2f temp2{ this->entities[j]->getVelocity() };
				this->entities[i]->setVelocity(temp2);
				this->entities[j]->setVelocity(temp1);
			}
		}
	}
}

void Field::collisionwithBullets()
{
	//这段的代码都能挪到别的地方去，先空着
}

void Field::updateExplosionSprite(sf::RectangleShape& display_shape)
{
	for (auto& i : this->explosion_animation_cache) {
		i.setPosition(
			i.getPosition().x * display_shape.getGlobalBounds().width + display_shape.getPosition().x,
			i.getPosition().y * display_shape.getGlobalBounds().height + display_shape.getPosition().y
		);
		i.setScale(
			i.getScale().x * display_shape.getGlobalBounds().width,
			i.getScale().y * display_shape.getGlobalBounds().height
		);
		this->explosion_animation.push_back(i);
	}

	for (size_t i{ 0 }; i < this->explosion_animation.size();i++) {
		if (this->explosion_animation[i].getFillColor().a <= (sf::Uint8)10) {
			this->explosion_animation.erase(this->explosion_animation.begin() + i);
		}
		else {
			sf::Uint8 a = this->explosion_animation[i].getFillColor().a - 10;
			this->explosion_animation[i].setFillColor(sf::Color::Color(this->explosion_animation[i].getFillColor().r, this->explosion_animation[i].getFillColor().g, this->explosion_animation[i].getFillColor().b, a));
		}
	}
}

void Field::update(sf::RectangleShape& display_shape)
{
	this->updateLogic();
	this->updateSprite(display_shape);
}

void Field::updateLogic()
{
	for (auto& i : this->entities) {
		i->updateLogic(this->bullets, this->entities, this->barrier_map);
	}
	for (auto& i : this->towers) {
		i->updateLogic(this->entities, this->bullets);
	}
	for (auto& i : this->bullets) {
		i->updateLogic();
	}
	this->collision();
	this->bulletTrigger();
	this->recycleBullet();
}

void Field::updateSprite(sf::RectangleShape& display_shape)
{
	this->updateExplosionSprite(display_shape);
	for (auto& i : this->entities) {
		i->updateSprite(this->size, display_shape);
	}
	for (auto& i : this->towers) {
		i->updateSprite(this->size, display_shape);
	}
	for (auto& i : this->bullets) {
		i->updateSprite(this->size, display_shape);
	}
}

void Field::render(sf::RenderTarget& target)
{
	for (auto& i : this->entities) {
		i->render(target);
	}
	for (auto& i : this->towers) {
		i->render(target);
	}
	for (auto& i : this->bullets) {
		i->render(target);
	}
	for (auto& i : this->explosion_animation) {
		target.draw(i);
	}
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
	for (auto& i : this->bullets) {
		delete i;
	}
	for (auto& i : this->entities) {
		delete i;
	}
}
