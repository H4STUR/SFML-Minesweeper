#include "Minefield.h"

//inits
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
												(this->grid * y) + position.y), tileType::empty));

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
	this->initField();
}

Minefield::~Minefield()
{
	this->clear();
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
	if (this->field[x][y].size() > 1)
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
	for (int x = 0; x < this->field.size(); x++)
	{
		for (int y = 0; y < this->field[x].size(); y++)
		{
			this->field[x][y].top()->render(target);
		}
	}
}

void Minefield::clear()
{

	for (int x = 0; x < this->field.size(); x++)
	{
		for (int y = 0; y < this->field[x].size(); y++)
		{
			while (!this->field[x][y].empty())
			{
				delete this->field[x][y].top();
				this->field[x][y].pop();
			}
		}
	}
}