#include "Bullet.h"

void Bullet::updateSprite(sf::Vector2u& size, sf::RectangleShape& display_shape)
{
	this->pic.setPosition(
		((this->position.x - (float)this->data_component.get("BULLET_RADIUS")) / (float)size.x) * display_shape.getGlobalBounds().width + display_shape.getPosition().x,
		((this->position.y - (float)this->data_component.get("BULLET_RADIUS")) / (float)size.y) * display_shape.getGlobalBounds().height + display_shape.getPosition().y
	);
	this->pic.setScale(
		(float)this->data_component.get("BULLET_RADIUS") * 2.f / size.x * display_shape.getGlobalBounds().width / this->pic.getLocalBounds().width,
		(float)this->data_component.get("BULLET_RADIUS") * 2.f / size.y * display_shape.getGlobalBounds().height / this->pic.getLocalBounds().height
	);
}

Bullet::Bullet(sf::Vector2u& pos, DataComponent& data_component, const sf::Vector2f& target_point)
	:data_component{ data_component },
	position{ pos },
	velocity{ 
		((float)target_point.x - this->position.x) *
		((float)this->data_component.get("BULLET_VELOCITY") / sqrtf(((float)target_point.x - this->position.x) * ((float)target_point.x - this->position.x) + ((float)target_point.y - this->position.y) * ((float)target_point.y - this->position.y))),
		((float)target_point.y - this->position.y) *
		((float)this->data_component.get("BULLET_VELOCITY") / sqrtf(((float)target_point.x - this->position.x) * ((float)target_point.x - this->position.x) + ((float)target_point.y - this->position.y) * ((float)target_point.y - this->position.y))) },
	is_dead{ false },
	collision_timer{ (unsigned int)std::min((this->data_component.get("SIZE_X") / 2.f + this->data_component.get("BULLET_RADIUS")) / std::abs(this->velocity.x),(this->data_component.get("SIZE_Y") / 2.f + this->data_component.get("BULLET_RADIUS")) / abs(this->velocity.y)) + (unsigned int)3 },
	able_to_collision{ false }
{
	this->pic.setFillColor(sf::Color::Black);
	this->pic.setRadius(100.f);
}

Bullet::~Bullet()
{
}

DataComponent& Bullet::getDataComponent()
{
	return this->data_component;
}

const sf::Vector2f& Bullet::getPos()
{
	return this->position;
}

void Bullet::setDead()
{
	this->is_dead = true;
}

const bool Bullet::isDead()
{
	return this->is_dead;
}

const bool Bullet::abletoCollision()
{
	return this->able_to_collision;
}

void Bullet::setVelocity(const sf::Vector2f& velocity)
{
	this->velocity = velocity;
}

const sf::Vector2f& Bullet::getVelocity()
{
	return this->velocity;
}

void Bullet::update(sf::Vector2u& size, sf::RectangleShape& display_shape)
{
	this->updateLogic();
	this->updateSprite(size, display_shape);
}

void Bullet::updateLogic()
{
	this->position += this->velocity;
	if (!able_to_collision) {
		this->collision_timer--;
		if (collision_timer == 0) {
			this->able_to_collision = true;
		}
	}
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->pic);
}
