#include "Minefield.h"

//inits

void Minefield::initBackground()
{
	this->background.setPosition(this->position);

	this->background.setSize(sf::Vector2f(
		this->size.x * this->grid,
		this->size.y * this->grid));

	this->background.setFillColor(sf::Color(50, 50, 50, 250));
}

void Minefield::initField()
{
	////	initializing and resizing minefield

	this->field.reserve(this->size.x);
	for (int x = 0; x < this->size.x; x++)
	{
		this->field.emplace_back(std::vector< std::stack<Tile*> >());

		this->field[x].reserve(this->size.y);
		for (int y = 0; y < this->size.y; y++)
		{
			this->field[x].emplace_back( std::stack<Tile* >());

			//adding tiles to stack

			this->field[x][y].push(new Tile(this->grid, sf::Vector2f(
										(this->grid * x) + position.x,
										(this->grid * y) + position.y), 9));
		}
	}
	
}

//Constructors && Destructors
Minefield::Minefield(float grid, sf::Vector2i& size, sf::Vector2f& position)
	: size(size), position(position)
{
	this->layers = 3;
	this->grid = grid;
	this->initBackground();
	this->initField();
}

Minefield::~Minefield()
{
	this->clear();
}

const bool Minefield::contains(sf::Vector2f& point) const
{
	if (this->background.getGlobalBounds().contains(point))
		return true;
	else
		return false;
}

void Minefield::setFlag(int x, int y)
{
	if (this->field[x][y].top()->getType() == tileType::full)
	{
		this->field[x][y].push(new Tile(this->grid, sf::Vector2f(
									(this->grid * x) + position.x,
									(this->grid * y) + position.y), tileType::flag));
		std::cout << "\nFLAG PLACED";
	}

}

void Minefield::openTile(int x, int y)
{
	if (!this->field[x][y].empty())
	{
		delete this->field[x][y].top();
		this->field[x][y].pop();
	}
	std::cout << "\n" << this->field[x][y].size() << "\n";
}

void Minefield::update(const float& deltaTime)
{
}

const void Minefield::render(sf::RenderTarget* target)
{
	target->draw(this->background);

	for (unsigned x = 0; x < this->field.size(); x++)
	{
		for (unsigned y = 0; y < this->field[x].size(); y++)
		{
			if(!this->field[x][y].empty())
				this->field[x][y].top()->render(target);
		}
	}
}

void Minefield::clear()
{

	for (unsigned x = 0; x < this->field.size(); x++)
	{
		for (unsigned y = 0; y < this->field[x].size(); y++)
		{
			while (!this->field[x][y].empty())
			{
				delete this->field[x][y].top();
				this->field[x][y].pop();
			}
		}
	}
}