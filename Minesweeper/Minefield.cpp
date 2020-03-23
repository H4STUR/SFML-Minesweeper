#include "Minefield.h"

//inits
void Minefield::initField()
{
	////	initializing and resizing minefield

	this->field.reserve(5);
	for (int x = 0; x < this->size.x; x++)
	{
		this->field.emplace_back(std::vector< std::vector<Tile*> >());

		for (int y = 0; y < this->size.y; y++)
		{
			this->field[x].reserve(5);
			this->field[x].emplace_back(std::vector<Tile* >());

			for (int z = 0; z < this->layers; z++)
			{
				this->field[x][y].reserve(3);
				this->field[x][y].emplace_back(new Tile(this->grid, sf::Vector2f(
														(this->grid * x) + position.x, 
														(this->grid * y) + position.y)));
			}
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
	//std::cout << "\n" << this->field.size() << "\n" << this->field[0].size() << "\n" << this->field[0][0].size();
	//std::cout << "\n" << this->size.x << "\n" << this->size.y;
}

Minefield::~Minefield()
{
	this->clear();
}

void Minefield::setFlag()
{
}

void Minefield::openTile()
{
}

void Minefield::update(const float& deltaTime)
{
}

const void Minefield::render(sf::RenderTarget* target)
{
	for (auto &x : this->field)
	{
		for (auto &y : x)
		{
			for (auto& z : y)
			{
				z->render(target);
			}
		}
	}
}

void Minefield::clear()
{
	for (auto& x : this->field)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				delete z;
			}
			y.clear();
		}
		x.clear();
	}
}