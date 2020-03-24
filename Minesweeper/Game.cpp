#include "stdafx.h"
#include "Game.h"

//Inits
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	//loading window settings
	this->data.loadSettings();
	this->data.SwitchDebugMode(true);

	if(data.fullstreen)
		this->window = new sf::RenderWindow(data.resolution, data.title, sf::Style::Fullscreen);
	else
		this->window = new sf::RenderWindow(data.resolution, data.title, sf::Style::Titlebar | sf::Style::Close);
	
	this->window->setFramerateLimit(data.FPSLimit);
	printf("Window Successfully created! \n");
}

void Game::initFont()
{
	//FONT STUFF
	if (this->font.loadFromFile("fonts/Arial.ttf"))
	{
		if (this->data.DebugMode)
			printf("Font Succesfuly Loaded!\n");
	}
	else
		printf("ERROR! Font Cannot be Loaded! :: MainMenuState -> initGui()\n");
}


void Game::initData()
{
	this->data.window = this->window;
	this->data.states = &this->states;
	this->data.font = &this->font;
}


void Game::initState()
{
	this->states.push(new MainMenuState(&this->data));
}

//Constructors && Destructos
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initData();
	this->initFont();
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
				sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
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