#include "Tile.h"


//Inits
void Tile::initTile()
{

	//setting texture for tiles next to bomb 
	if (this->type >= 1 && this->type <= 8)
	{
		// tile images with 1-8 numbers are named 1.png ... 8.png
		// "assets/ .png" - because space (index [7]) is replaced with number
		// this->type + 48 - ascii numbers - just type number but char

		std::string path = "assets/ .png";
		path[7] = static_cast<char>(this->type + 48);
		this->tex.loadFromFile(path);
	}

	//default settings for base tile states
	switch (this->type)
	{
		case tileType::empty:
		{
			this->bomb = false;
			this->tex.loadFromFile("assets/empty.png");

		}break;	

		case tileType::full:
		{
			this->bomb = false;
			this->tex.loadFromFile("assets/tile.png");

		}break;	

		case tileType::flag:
		{
			this->bomb = false;
			this->tex.loadFromFile("assets/flag.png");

		}break;

		case tileType::bomb:
		{
			this->bomb = true;
			this->tex.loadFromFile("assets/bomb.png");

		}break;
	}
}


Tile::Tile()
{
	this->initTile();
}

//Constructors && Destructors
Tile::Tile(float grid, sf::Vector2f position, short type)
{
	this->type = type;
	this->initTile();
	this->shape.setPosition(position);
	this->shape.setSize(sf::Vector2f(grid, grid));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setTexture(&tex);
}

Tile::~Tile()
{

}

//Accessors
const short Tile::getType() const
{
	return this->type;
}

//Setters
void Tile::setBomb()
{
	this->bomb = true;
}


void Tile::update(const float& deltaTime)
{

}

void Tile::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}