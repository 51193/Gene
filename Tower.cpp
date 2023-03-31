#include "Tower.h"

std::map<std::string, TowerTemplate> Tower::tower_lib;

void Tower::updateSprite(sf::Vector2u& size, sf::RectangleShape& display_shape)
{
	this->sprite.setScale(
		(float)this->data_component.get("SIZE_X") / size.x * display_shape.getGlobalBounds().width / this->sprite.getLocalBounds().width,
		(float)this->data_component.get("SIZE_Y") / size.y * display_shape.getGlobalBounds().height / this->sprite.getLocalBounds().height
	);
	this->sprite.setPosition(
		(((float)this->pos.x - (float)this->data_component.get("SIZE_X") * (float)0.5) / (float)size.x) * display_shape.getGlobalBounds().width + display_shape.getPosition().x,
		(((float)this->pos.y - (float)this->data_component.get("SIZE_Y") * (float)0.5) / (float)size.y) * display_shape.getGlobalBounds().height + display_shape.getPosition().y
	);

	this->range.setScale(
		(float)this->data_component.get("RANGE") * 2.f / size.x * display_shape.getGlobalBounds().width / this->range.getLocalBounds().width,
		(float)this->data_component.get("RANGE") * 2.f / size.y * display_shape.getGlobalBounds().height / this->range.getLocalBounds().height
	);
	this->range.setPosition(
		(((float)this->pos.x - (float)this->data_component.get("RANGE")) / (float)size.x) * display_shape.getGlobalBounds().width + display_shape.getPosition().x,
		(((float)this->pos.y - (float)this->data_component.get("RANGE")) / (float)size.y) * display_shape.getGlobalBounds().height + display_shape.getPosition().y
	);

	this->outline.setScale(
		(float)this->data_component.get("SIZE_X") / size.x * display_shape.getGlobalBounds().width / this->outline.getLocalBounds().width,
		(float)this->data_component.get("SIZE_Y") / size.y * display_shape.getGlobalBounds().height / this->outline.getLocalBounds().height
	);
	this->outline.setPosition(
		(((float)this->pos.x - (float)this->data_component.get("SIZE_X") * (float)0.5) / (float)size.x) * display_shape.getGlobalBounds().width + display_shape.getPosition().x,
		(((float)this->pos.y - (float)this->data_component.get("SIZE_Y") * (float)0.5) / (float)size.y) * display_shape.getGlobalBounds().height + display_shape.getPosition().y
	);

	this->animation_component.play("default");//记得改这段
}

Tower::Tower(const std::string& name, sf::Vector2u& pos)
	:pos{ pos }, is_ready{ true }, timer{ 0 }
{
	if (!Tower::tower_lib[name].isLoaded()) {
		Tower::tower_lib[name].loadFromFile("Tower\\" + name);
	}

	this->range.setOutlineColor(sf::Color::Black);
	this->range.setOutlineThickness(1.f);
	this->range.setFillColor(sf::Color::Color(224, 224, 224, 64));
	this->range.setRadius(100.f);

	this->outline.setOutlineColor(sf::Color::Black);
	this->outline.setOutlineThickness(2.f);
	this->outline.setFillColor(sf::Color::Transparent);
	this->outline.setSize(sf::Vector2f(100.f, 100.f));

	this->animation_component.loadFromTemplate(this->sprite, Tower::tower_lib[name].getAnimationComponentTemplate());
	this->data_component.loadFromTemplate(Tower::tower_lib[name].getDataComponentTemplate());

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

DataComponent& Tower::getDataComponent()
{
	return this->data_component;
}

const sf::Sprite Tower::getSprite()
{
	return this->sprite;
}

void Tower::shoot(std::vector<Entity*>& entities, std::vector<Bullet*>& bullets)
{
	for (auto& i : entities) {
		if (!i->isDead() && this->is_ready) {

			if (
				((float)this->pos.x - i->getPos().x) * ((float)this->pos.x - i->getPos().x) + ((float)this->pos.y - i->getPos().y) * ((float)this->pos.y - i->getPos().y)
				<= ((float)this->data_component.get("RANGE") + (float)i->getDataComponent().get("RADIUS")) * ((float)this->data_component.get("RANGE") + (float)i->getDataComponent().get("RADIUS"))
				) {
				this->is_ready = false;
				bullets.push_back(new Bullet(this->pos, this->data_component, i->getPos()));
			}

		}
	}
}

const bool Tower::isReady()
{
	return this->is_ready;
}

void Tower::update(sf::Vector2u& size, sf::RectangleShape& display_shape, std::vector<Entity*>& entities, std::vector<Bullet*>& bullets)
{
	this->updateSprite(size, display_shape);
}

void Tower::updateLogic(std::vector<Entity*>& entities, std::vector<Bullet*>& bullets)
{
	if (!this->is_ready) {
		this->timer++;
		if (this->timer >= this->data_component.get("COOL_DOWN")) {
			this->timer = 0;
			this->is_ready = true;
		}
	}
	this->shoot(entities, bullets);
}

void Tower::render(sf::RenderTarget& target)
{
	target.draw(this->range);
	target.draw(this->sprite);
	target.draw(this->outline);
}
