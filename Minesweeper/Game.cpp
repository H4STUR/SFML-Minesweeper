#include "stdafx.h"
#include "Game.h"

//Inits
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	if(data.fullstreen)
		this->window = new sf::RenderWindow(data.resolution, data.title, sf::Style::Fullscreen);
	else
		this->window = new sf::RenderWindow(data.resolution, data.title, sf::Style::Titlebar | sf::Style::Close);
	
	this->window->setFramerateLimit(data.FPSLimit);
	printf("Window Successfully created! \n");
}

void Game::initSettings()
{
	data.loadSettings();
	data.SwitchDebugMode(true);
}

void Game::initData()
{
	data.window = this->window;
	data.states = &this->states;
}


void Game::initState()
{
	this->states.push(new MainMenuState(&this->data));
}

//Constructors && Destructos
Game::Game()
{
	this->initVariables();
	this->initSettings();
	this->initWindow();
	this->initData();
	this->initState();
}


Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//Functions
void Game::run()
{
	while (window->isOpen())
	{
		this->update();
		this->updateDeltaTime();
		this->render();
	}
}

void Game::update()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
			case sf::Event::Closed:
			{
				this->window->close();
			}break;

			case sf::Event::Resized:
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window->setView(sf::View(visibleArea));
			}break;
		}
	}

	//Updates current state
	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->DeltaTime);

			if (this->states.top()->getQuit())
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	else
		this->window->close();
}

void Game::updateDeltaTime()
{
	this->DeltaTime = clock.restart().asSeconds();
}

void Game::render()
{
	this->window->clear();

	//Renders current state
	if(!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}