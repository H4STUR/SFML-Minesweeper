#ifndef _GAMESTATE
#define _GAMESTATE

#include "State.h"
#include "Minefield.h"

class GameState : public State
{
public:
	GameState(Data* data, sf::Vector2i fieldSize);
	~GameState();

	//Functions
	virtual void updateInput(const float& deltaTime);
	void updateGui();
	virtual void update(const float& deltaTime);
	virtual void render(sf::RenderTarget* target = nullptr);
private:
	//variables
	Minefield* minefield;
	gui::Counter* counter;

	sf::RectangleShape BackGround;
	sf::RectangleShape topBar;
	sf::RectangleShape selector;

	sf::Vector2i fieldSize;
	sf::Vector2f fieldPosition;

	//
	float grid;
	float padding;
	float topBarHeight;

	//Inits
	void init();
	void resizeWindow();
	void initGui();
};

#endif //!_GAMESTATE