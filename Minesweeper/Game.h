#ifndef _GAME
#define _GAME

#include "stdafx.h"
#include "Settings.h"
#include "State.h"
#include "MainMenuState.h"

//Forward declarations
class Settings;
class Data;
class State;
class MainMenuState;

class Game
{
public:
	Game();
	virtual ~Game();

	//Functions
	void run();
	void update();
	void updateDeltaTime();
	void render();

private:
	//Variables
	sf::RenderWindow* window;
	sf::Event event;
	sf::Clock clock;
	std::stack<State*> states;
	float DeltaTime;

	Data data;
	

	//Inits
	void initVariables();
	void initWindow();
	void initSettings();
	void initData();
	void initState();
};

#endif //!_GAME