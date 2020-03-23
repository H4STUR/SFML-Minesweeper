#include "stdafx.h"
#include "State.h"


State::State(Data* data)
	:data(data)
{
	this->quit = false;
	this->paused = false;
	this->window = this->data->window;
	this->keytime = 0.f;
	this->maxKeytime = 20.f;
}


State::~State()
{
}

const bool & State::getQuit() const
{
	return this->quit;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->maxKeytime)
	{
		this->keytime = 0.f;

		return true;
	}
	return false;
}

void State::endState()
{
	this->quit = true;
	printf("ENDING STATE...\n");
}

void State::pauseState()
{
	this->paused = true;
	printf("STATE PAUSED...\n");
}

void State::unpauseState()
{
	this->paused = false;
	printf("STATE UNPAUSED...\n");
}

void State::updateKeytime(const float & deltaTime)
{
	if (this->keytime < this->maxKeytime)
	{
		this->keytime += 100.f * deltaTime;
	}
}

void State::updateMousePos(sf::View * view, float grid)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->data->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2i(
				static_cast<int>(this->mousePosView.x / grid), 
				static_cast<int>(this->mousePosView.y / grid));
}
