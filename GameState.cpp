#include "GameState.h"

void GameState::init()
{
	this->initUI();
	this->field = new Field("Save\\test.sav");
	this->field->updateSprite(this->squares["field_area"]);
}

void GameState::initUI()
{
	float a{ 1.f };

	this->squares["background"].setFillColor(sf::Color::White);
	this->squares["background"].setPosition(0.f, 0.f);
	this->squares["background"].setSize(sf::Vector2f((float)this->window.getSize().x, (float)this->window.getSize().y));

	this->squares["field_area"].setFillColor(sf::Color::White);
	this->squares["field_area"].setOutlineColor(sf::Color::Black);
	this->squares["field_area"].setOutlineThickness(3.f);
	this->squares["field_area"].setPosition(3.f, 3.f);

	if ((float)this->window.getSize().x / (float)this->window.getSize().y > 16.f / 9.f) {
		this->squares["field_area"].setSize(sf::Vector2f((float)(this->window.getSize().y * a * (16.f / 9.f)), (float)(this->window.getSize().y * a)));
	}
	else {
		this->squares["field_area"].setSize(sf::Vector2f((float)(this->window.getSize().x * a), (float)(this->window.getSize().x * a * (9.f / 16.f))));
	}
}

void GameState::renderUI(sf::RenderTarget& target)
{
	for (auto& i : this->squares) {
		target.draw(i.second);
	}
}

GameState::GameState(sf::RenderWindow& window, sf::Font& font, std::stack<State*>& states)
	:State{ window, font, states }, timer{ 0.f }, fixed_time{ 1/60.f }
{
	this->init();
}

GameState::~GameState()
{
}

void GameState::update(const float& dt)
{
	this->updateMousePosition();

	this->timer += dt;
	if (this->timer > this->fixed_time) {
		unsigned int frames = (unsigned int)(this->timer / this->fixed_time);
		for (size_t j{ 0 }; j < frames; j++) {
			//update ���̵Ĺ̶�֡��
			this->field->update(this->squares["field_area"]);
		}
		this->timer = this->timer - frames * fixed_time;
	}
}

void GameState::render(sf::RenderTarget& target)
{
	this->renderUI(target);

	this->field->render(target);
}
