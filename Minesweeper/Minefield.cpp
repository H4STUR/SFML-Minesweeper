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

void Minefield::reserveField()
{
	////	initializing and resizing minefield
	int amount = 0;
	this->field.reserve(this->size.x);
	for (int x = 0; x < this->size.x; x++)
	{
		this->field.emplace_back(std::vector< std::stack<Tile*> >());

		this->field[x].reserve(this->size.y);

		for (int y = 0; y < this->size.y; y++)
		{
			this->field[x].emplace_back( std::stack<Tile* >());

			std::cout << amount << " ";
			amount++;

			this->field[x][y].push(new Tile(this->grid, sf::Vector2f(
										(this->grid * x) + position.x,
										(this->grid * y) + position.y), tileType::full));
		}
		std::cout << "\n";
	}
	
	if (!this->areBombGenerated)
		this->generateBombs();
}

//Constructors && Destructors
Minefield::Minefield(float grid, sf::Vector2i& size, sf::Vector2f& position, unsigned short bombAmount)
	: size(size), position(position)
{
	this->layers = 3;
	this->grid = grid;
	this->areBombGenerated = false;
	this->bombAmount = bombAmount;
	this->initBackground();
	this->reserveField();
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

//Gameplay functions
void Minefield::setFlag(int x, int y)
{
	if (!this->field[x][y].empty())
	{
		if (this->field[x][y].top()->getType() == tileType::full)
		{
			this->field[x][y].push(new Tile(this->grid, sf::Vector2f(
				(this->grid * x) + position.x,
				(this->grid * y) + position.y), tileType::flag));
			std::cout << "\nFLAG PLACED";
		}
		else if (this->field[x][y].top()->getType() == tileType::flag)
		{
			delete this->field[x][y].top();
			this->field[x][y].pop();
		}
	}
	else return;
}

void Minefield::openTile(int x, int y)
{
	if (x >= 0 && x < this->size.x && y >= 0 && y < this->size.y)
	{
		if (!this->field[x][y].empty())
			if (this->field[x][y].top()->getType() == tileType::full)
			{
				delete this->field[x][y].top();
				this->field[x][y].pop();

				if(this->field[x][y].empty())
					this->openEmptyField(sf::Vector2i(x, y));
			}
	}
	else return;
}

void Minefield::generateBombs()
{
	unsigned short i = 0;
	srand(time(NULL));

	//!!!
	//! 
	//! Here's problem, field doesn't generate itself properly
	//! 
	//!!!

	//while (i < 1)
	//{
	//	
	//	sf::Vector2i bomb = sf::Vector2i(rand() % this->size.x, rand() % this->size.y);

	//	std::cout << "\nX: " << bomb.x << "  Y: " << bomb.y;
	//	if (this->field[bomb.x][bomb.x].empty())
	//	{
	//		this->field[bomb.x][bomb.x].push(new Tile(this->grid, sf::Vector2f(
	//			(this->grid * bomb.x) + position.x,
	//			(this->grid * bomb.y) + position.y), tileType::bomb));

	//		i++;
	//	}
	//}
	this->areBombGenerated = true;
}

void Minefield::openEmptyField(sf::Vector2i pos)
{
	for (int x = pos.x - 1; x <= pos.x + 1; x++)
		for (int y = pos.y - 1; y <= pos.y + 1; y++)
		{
				this->openTile(x, y);
		}

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

const bool Minefield::canBeOpened(sf::Vector2f pos) const
{
	return (this->field[pos.x][pos.y].top()->getType() == tileType::empty);
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