#include "Button.h"

Button::Button(
	const float x, const float y,
	const float width, const float height,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color) :
	button_state{ BUTTON_IDLE },
	idle_color{ idle_color }, hover_color{ hover_color }, active_color{ active_color },
	idle_textcolor{ sf::Color::Transparent }, hover_textcolor{ sf::Color::Transparent }, active_textcolor{ sf::Color::Transparent }, font{ nullptr }
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->shape.setFillColor(this->idle_color);
}

Button::Button(
	const float x, const float y,
	const float width, const float height,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color idle_textcolor, sf::Color hover_textcolor, sf::Color active_textcolor, sf::Font* font, const std::string& text) :
	button_state{ BUTTON_IDLE },
	idle_color{ idle_color }, hover_color{ hover_color }, active_color{ active_color },
	idle_textcolor{ idle_textcolor }, hover_textcolor{ hover_textcolor }, active_textcolor{ active_textcolor }, font{ font }
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(static_cast<unsigned int>(height) / 3);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - (this->text.getCharacterSize() / 2.f)
	);

	this->text.setFillColor(this->idle_textcolor);
	this->shape.setFillColor(this->idle_color);
}

Button::Button(
	const float x, const float y,
	const float width, const float height,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	const float outline_thickness) :
	button_state{ BUTTON_IDLE },
	idle_color{ idle_color }, hover_color{ hover_color }, active_color{ active_color },
	idle_textcolor{ sf::Color::Transparent }, hover_textcolor{ sf::Color::Transparent }, active_textcolor{ sf::Color::Transparent }, font{ nullptr }
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setOutlineThickness(outline_thickness);

	this->shape.setFillColor(this->idle_color);
}

Button::Button(
	const float x, const float y,
	const float width, const float height,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color idle_textcolor, sf::Color hover_textcolor, sf::Color active_textcolor, sf::Font* font, const std::string& text,
	const float outline_thickness)
	:
	button_state{ BUTTON_IDLE },
	idle_color{ idle_color }, hover_color{ hover_color }, active_color{ active_color },
	idle_textcolor{ idle_textcolor }, hover_textcolor{ hover_textcolor }, active_textcolor{ active_textcolor }, font{ font }
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setOutlineThickness(outline_thickness);

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setCharacterSize(static_cast<unsigned int>(height) / 3);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - (this->text.getCharacterSize() / 2.f)
	);

	this->text.setFillColor(this->idle_textcolor);
	this->shape.setFillColor(this->idle_color);
}

Button::~Button()
{

}

const bool Button::isPressed()
{
	if (this->button_state == BUTTON_ACTIVE)return 1;
	return 0;
}

void Button::update(const sf::Vector2f& mousePos)
{
	this->button_state = BUTTON_IDLE;
	if (this->shape.getGlobalBounds().contains(mousePos)) {
		this->button_state = BUTTON_HOVER;
	}
	if (this->shape.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->button_state = BUTTON_ACTIVE;
	}
	this->updateColor();
}

void Button::updateColor()
{
	switch (button_state)
	{
	case BUTTON_IDLE:
		this->shape.setFillColor(this->idle_color);
		this->text.setFillColor(this->idle_textcolor);
		break;
	case BUTTON_HOVER:
		this->shape.setFillColor(this->hover_color);
		this->text.setFillColor(this->hover_textcolor);
		break;
	case BUTTON_ACTIVE:
		this->shape.setFillColor(this->active_color);
		this->text.setFillColor(this->active_textcolor);
		break;
	default:
		this->shape.setFillColor(this->idle_color);
		this->text.setFillColor(this->idle_textcolor);
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

void Button::moveto(float x, float y)
{
	this->shape.setPosition(x, y);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - (this->text.getCharacterSize() / 2.f)
	);
}

const short unsigned int Button::getButtonState()
{
	return button_state;
}
