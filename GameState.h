#ifndef GAMESTATE_H
#define GAMESTATE_H

#include<map>

#include"Button.h"

#include"State.h"
#include"Field.h"

class GameState :
	public State
{
protected:

	std::map<std::string, sf::RectangleShape*>squares;

	float timer;
	float fixed_time;//表示棋盘上每帧需要的时间

	Field* field;

	void init();//初始化函数都应该扔进这个函数里

	void initUI();


	void renderUI(sf::RenderTarget& target);

public:
	GameState(sf::RenderWindow& window, sf::Font& font, std::stack<State*>& states);
	~GameState();

	void update(const float& dt);
	void render(sf::RenderTarget& target);

};

#endif