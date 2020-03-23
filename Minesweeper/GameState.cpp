#include "GameState.h"

void GameState::resizeWindow()
{
	this->data->Resize(sf::VideoMode(
		(this->fieldSize.x * this->grid) + this->padding *2,
		(this->fieldSize.y * this->grid) + (this->padding *2) + this->topBarHeight
	));
}

//Inits
void GameState::init()
{
	//width and height of single tile
	this->grid = 25;

	//margin
	this->padding = 5.f;


	this->topBarHeight = 50.f;

	//position of mine field
	this->fieldPosition = sf::Vector2f(this->padding, this->topBarHeight + this->padding);
}

void GameState::initGui()
{
	//Background stuff
	{
		this->BackGround.setPosition(sf::Vector2f(0.f, 0.f));
		this->BackGround.setSize(sf::Vector2f(
			static_cast<float>(this->data->resolution.width), 
			static_cast<float>(this->data->resolution.height)));
		this->BackGround.setFillColor(sf::Color(80, 80, 80, 255));
	}
	//Top Bar stuff
	{
		this->topBar.setPosition(sf::Vector2f(this->padding, this->padding));
		this->topBar.setSize(sf::Vector2f(static_cast<float>(this->data->resolution.width) - this->padding*2, this->topBarHeight));
		this->topBar.setFillColor(sf::Color(80, 80, 80, 255));
		this->topBar.setOutlineThickness(-3);
		this->topBar.setOutlineColor(sf::Color(60, 60, 60, 255));
	}

	//Selector stuff
	{
		this->selector.setSize(sf::Vector2f(this->grid, this->grid));
		this->selector.setFillColor(sf::Color(20, 20, 20, 30));
		this->selector.setOutlineThickness(-1);
		this->selector.setOutlineColor(sf::Color::Black);
	}
}

//Constructors && Destructors
GameState::GameState(Data* data, sf::Vector2i fieldSize)
	:State(data), fieldSize(fieldSize)
{
	this->init();
	this->resizeWindow();
	this->initGui();

	this->minefield = new Minefield(this->grid, this->fieldSize, this->fieldPosition);
}

GameState::~GameState()
{
	delete this->minefield;
}

void GameState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && this->getKeytime())
	{
		this->data->Resize(this->data->defaultResolution);
		this->endState();
	}

}

void GameState::updateGui()
{
	//sets selector on tiles

	if (this->mousePosView.y > this->topBarHeight &&
		this->mousePosGrid.x < this->fieldSize.x &&
		this->mousePosGrid.x >= 0)
	{
		this->selector.setPosition(sf::Vector2f(
			this->mousePosGrid.x * this->grid + this->padding,
			this->mousePosGrid.y * this->grid + this->padding));
	}
}

void GameState::update(const float& deltaTime)
{
	this->updateInput(deltaTime);
	this->updateMousePos(nullptr, this->grid);
	this->updateKeytime(deltaTime);
	this->updateGui();
}

void GameState::render(sf::RenderTarget* target)
{
	target->draw(this->BackGround);
	target->draw(this->topBar);
	this->minefield->render(target);
	
	//Gselector
	target->draw(this->selector);
}


