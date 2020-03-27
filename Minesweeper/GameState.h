#ifndef _GAMESTATE
#define _GAMESTATE

#include "State.h"
#include "Minefield.h"

enum difficulty
{
	easy = 0,
	medium,
	hard
};

class GameState : public State
{
public:
	GameState(Data* data, sf::Vector2i fieldSize);
	~GameState();

	//Functions
	virtual void updateInput(const float& deltaTime);
	void updateGui();
	virtual void update(const float& deltaTime);
	void updateButtons(const float& deltaTime);
	virtual void render(sf::RenderTarget* target = nullptr);
private:
	//variables
	Minefield* minefield;
	gui::Counter* counter;
	gui::Timer* timer;
	gui::Button* restartButton;

	sf::Texture restartButtonImage;
	sf::RectangleShape BackGround;
	sf::RectangleShape topBar;
	sf::RectangleShape selector;

	sf::Vector2i fieldSize;
	sf::Vector2f fieldPosition;

	sf::Time currentTime;
	sf::Time bestTime;

	//
	float grid;
	float padding;
	float topBarHeight;

	bool gameStarted;

	//Inits
	void init();
	void resizeWindow();
	void initGui();
};

#endif //!_GAMESTATE