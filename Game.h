#ifndef GAME_H
#define GAME_H

#include"MainMenu.h"

class Game
{
private:

	//������ر���

	sf::RenderWindow* window;

	//�¼�����

	sf::Event event;

	//����ˢ����ر���

	sf::Clock dt_clock;
	float dt;

	//�������

	sf::Font font;

	//State����

	std::stack<State*>states;

	//��ʼ��

	void init();

	void initWindow();
	void initFont();
	void initStates();

	//��ɢupdate����

	void updateDt();
	void updateSFMLEvent();

public:
	//���캯������������

	Game();
	~Game();

	//���ܺ���

	void update();
	void render();
	void run();

};

#endif GAME_H