#ifndef _STATE
#define _STATE

#include "stdafx.h"
#include "Settings.h"
#include "GUI.h"

class Data;

class State
{
public:
	State(Data* data);
	virtual ~State();

	//Functions

	const bool& getQuit() const;
	const bool getKeytime();

	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateKeytime(const float& deltaTime);
	virtual void updateMousePos(sf::View* view = nullptr, float grid = 1.f);
	virtual void update(const float& deltaTime) = 0;
	virtual void updateInput(const float& deltaTime) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

protected:
	//variables
	Data* data;
	sf::RenderWindow* window;
	float keytime;
	float maxKeytime;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2i mousePosGrid;

private:
	//Variables
	bool quit;
	bool paused;
};

#endif // !_STATE