#include "Tower.h"

std::map<std::string, TowerTemplate> Tower::tower_lib;

Tower::Tower(const std::string& name, sf::Vector2u& pos) :
	pos{ pos }
{
	if (!Tower::tower_lib[name].isLoaded()) {
		Tower::tower_lib[name].loadFromFile("Tower\\" + name);
	}

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

void Tower::update(sf::Vector2u& size, sf::RectangleShape& display_shape, sf::RenderWindow& window)
{
	this->sprite.setPosition(
		(this->pos.x / size.x) * display_shape.getGlobalBounds().width + display_shape.getPosition().x,
		(this->pos.y / size.y) * display_shape.getGlobalBounds().height + display_shape.getPosition().y
	);
	this->sprite.setScale(
		(float)this->data_component.get("SIZE_X") / size.x * display_shape.getGlobalBounds().width / this->sprite.getLocalBounds().width,
		(float)this->data_component.get("SIZE_Y") / size.y * display_shape.getGlobalBounds().height / this->sprite.getLocalBounds().height
	);

	this->animation_component.play("default");//记得改这段
}

void Tower::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
