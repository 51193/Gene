#include "Entity.h"

DataComponentTemplate Entity::data_component_template;

Entity::Entity(sf::Vector2u pos)
	:pos{ pos }, health_point{ 0 }, is_dead{ false }, velocity{ 0.f,0.f }
{
	this->init();
}

Entity::~Entity()
{
}

void Entity::init()
{
	this->initDataComponent();
	this->initAppearance();

	this->assignVelocity(sf::Vector2f(0.f, 5.f));
}

void Entity::initDataComponent()
{
	if (!this->data_component_template.isLoaded()) {
		this->data_component_template.loadFromFile("Entity\\data.dat");
	}

	this->data_component.loadFromTemplate(this->data_component_template);

	this->health_point = (int)this->data_component.get("HEALTH");
}

void Entity::initAppearance()
{
	this->appearance["body"].setRadius(100.f);
	this->appearance["body"].setFillColor(sf::Color::Color(0, 255, 255));
	this->appearance["body"].setOutlineThickness(2.f);
	this->appearance["body"].setOutlineColor(sf::Color::Black);
}

void Entity::assignVelocity(const sf::Vector2f& velocity)
{
	this->velocity += velocity;

	float v = sqrtf(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y);
	if (v > (float)this->data_component.get("MAX_VELOCITY")) {
		this->velocity = sf::Vector2f((float)this->data_component.get("MAX_VELOCITY") / v * this->velocity.x, (float)this->data_component.get("MAX_VELOCITY") / v * this->velocity.y);
	}
}

void Entity::setVelocity(const sf::Vector2f& velocity)
{
	this->velocity = velocity;
}

void Entity::setPos(const sf::Vector2f& pos)
{
	this->pos = pos;
}

void Entity::move()
{
	this->pos += this->velocity;

	this->friction();
}

void Entity::friction()
{
	float a = 100.f;

	if (
		this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y <=
		(float)this->data_component.get("FRICTION") / a * (float)this->data_component.get("FRICTION") / a
		) {
		this->velocity = sf::Vector2f(0.f, 0.f);
	}
	else {
		this->velocity -= sf::Vector2f(
			(float)this->data_component.get("FRICTION") / a / sqrtf(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y) * this->velocity.x,
			(float)this->data_component.get("FRICTION") / a / sqrtf(this->velocity.x * this->velocity.x + this->velocity.y * this->velocity.y) * this->velocity.y
		);
	}
}

void Entity::eyesight(std::vector<Bullet*>& bullets, std::vector<Entity*>& entities, std::vector<Barrier>& barrier_map)
{
	this->eye_sight.clear();

	unsigned int eye_sight_count = this->data_component.get("EYE_SIGHT_COUNT");
	unsigned int eye_sight_length = this->data_component.get("EYE_SIGHT_LENGTH");

	float eye_sight_deviation_angle = (2.f * (float)3.1415926535) / (float)eye_sight_count;

	for (size_t i{ 0 }; i < eye_sight_count; i++) {
		this->eye_sight.push_back(EyeSight{ this->pos + (float)eye_sight_length * sf::Vector2f(std::cosf(eye_sight_deviation_angle * i), std::sinf(eye_sight_deviation_angle * i)), (float)eye_sight_length, 0.f });
	}
	for (auto& i : this->eye_sight) {
		for (auto& j : bullets) {
			if (JudgeFunctions::CircleandLine(j->getPos(), (float)j->getDataComponent().get("BULLET_RADIUS"), this->pos, i.point)) {

				float verctical_length = JudgeFunctions::CircleandLineVerticalLength(j->getPos(), (float)j->getDataComponent().get("BULLET_RADIUS"), this->pos, i.point);

				float temp_length =
					sqrtf(
						JudgeFunctions::PointDistance(this->pos, j->getPos()) * JudgeFunctions::PointDistance(this->pos, j->getPos()) -
						verctical_length * verctical_length
					) -
					sqrtf(
						(float)j->getDataComponent().get("BULLET_RADIUS") * (float)j->getDataComponent().get("BULLET_RADIUS") -
						verctical_length * verctical_length
					);

				if (i.remain_length > temp_length) {
					i.remain_length = temp_length;
					i.output_strength = 4.f * (eye_sight_length - i.remain_length) / eye_sight_length;
				}

			}
		}

		for (auto& j : entities) {
			if (j != this) {
				if (JudgeFunctions::CircleandLine(j->getPos(), (float)j->getDataComponent().get("RADIUS"), this->pos, i.point)) {

					float verctical_length = JudgeFunctions::CircleandLineVerticalLength(j->getPos(), (float)j->getDataComponent().get("RADIUS"), this->pos, i.point);
					float total_length = JudgeFunctions::PointDistance(this->pos, i.point);

					float temp_length =
						sqrtf(
							JudgeFunctions::PointDistance(this->pos, j->getPos()) * JudgeFunctions::PointDistance(this->pos, j->getPos()) -
							verctical_length * verctical_length
						) -
						sqrtf(
							(float)j->getDataComponent().get("RADIUS") * (float)j->getDataComponent().get("RADIUS") -
							verctical_length * verctical_length
						);

					if (i.remain_length > temp_length) {
						i.remain_length = temp_length;
						i.output_strength = 4.f * (eye_sight_length - i.remain_length) / eye_sight_length;
					}

				}
			}
		}

		for (auto& j : barrier_map) {

		}
	}
}

const sf::Vector2f& Entity::getPos()
{
	return this->pos;
}

const sf::Vector2f& Entity::getVelocity()
{
	return this->velocity;
}

DataComponent& Entity::getDataComponent()
{
	return this->data_component;
}

const bool Entity::isDead()
{
	return this->is_dead;
}

const int Entity::getHealthPoint()
{
	return this->health_point;
}

void Entity::getHurt(unsigned int damage)
{
	this->health_point -= damage;
	if (health_point <= 0) {
		is_dead = true;
	}
}

void Entity::update(sf::Vector2u& size, sf::RectangleShape& display_shape, std::vector<Bullet*>& bullets, std::vector<Entity*>& entities, std::vector<Barrier>& barrier_map)
{
	if (!is_dead) {
		this->updateLogic(bullets, entities, barrier_map);
		this->updateSprite(size, display_shape);
	}
}

void Entity::updateLogic(std::vector<Bullet*>& bullets, std::vector<Entity*>& entities, std::vector<Barrier>& barrier_map)
{
	if (!is_dead) {
		this->eyesight(bullets, entities, barrier_map);
		this->move();
	}
}

void Entity::updateSprite(sf::Vector2u& size, sf::RectangleShape& display_shape)
{
	if (!is_dead) {
		this->appearance["body"].setScale(
			(float)this->data_component.get("RADIUS") * 2.f / size.x * display_shape.getGlobalBounds().width / this->appearance["body"].getLocalBounds().width,
			(float)this->data_component.get("RADIUS") * 2.f / size.y * display_shape.getGlobalBounds().height / this->appearance["body"].getLocalBounds().height
		);
		this->appearance["body"].setPosition(
			((this->pos.x - (float)this->data_component.get("RADIUS")) / (float)size.x) * display_shape.getGlobalBounds().width + display_shape.getPosition().x,
			((this->pos.y - (float)this->data_component.get("RADIUS")) / (float)size.y) * display_shape.getGlobalBounds().height + display_shape.getPosition().y
		);
	}
}

void Entity::render(sf::RenderTarget& target)
{
	if (!is_dead) {
		for (auto& i : this->appearance) {
			target.draw(i.second);
		}
	}
}
