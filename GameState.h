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
	float fixed_time;//��ʾ������ÿ֡��Ҫ��ʱ��

	Field* field;

	void init();//��ʼ��������Ӧ���ӽ����������

	void initUI();


	void renderUI(sf::RenderTarget& target);

public:
	GameState(sf::RenderWindow& window, sf::Font& font, std::stack<State*>& states);
	~GameState();

	void update(const float& dt);
	void render(sf::RenderTarget& target);

};

#endif