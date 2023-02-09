#ifndef BUTTON_H
#define BUTTON_H

#include<SFML/Graphics.hpp>

enum button_state {
	BUTTON_IDLE = 0,
	BUTTON_HOVER,
	BUTTON_ACTIVE
};

class Button {
private:
	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;

	sf::Color idle_color;
	sf::Color hover_color;
	sf::Color active_color;

	sf::Color idle_textcolor;
	sf::Color hover_textcolor;
	sf::Color active_textcolor;

	short unsigned int button_state;

public:
	
	Button(
		const float x, const float y,
		const float width, const float height,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color
	);
	Button(
		const float x, const float y,
		const float width, const float height,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
		sf::Color idle_textcolor, sf::Color hover_textcolor, sf::Color active_textcolor, sf::Font* font, const std::string& text
	);
	Button(
		const float x, const float y,
		const float width, const float height,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
		const float outline_thickness
	);
	Button(
		const float x, const float y,
		const float width, const float height,
		sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
		sf::Color idle_textcolor, sf::Color hover_textcolor, sf::Color active_textcolor, sf::Font* font, const std::string& text,
		const float outline_thickness
	);

	~Button();

	const bool isPressed();

	//¹¦ÄÜ

	void update(const sf::Vector2f& mousePos);
	void updateColor();
	void render(sf::RenderTarget& target);

	void moveto(float x, float y);

	const short unsigned int getButtonState();
};

#endif