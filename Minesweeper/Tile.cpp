#include "Tile.h"


//Inits
void Tile::initTile()
{
	this->tex.loadFromFile("assets/tile.png");
}


Tile::Tile()
{
	this->initTile();
}

//Constructors && Destructors
Tile::Tile(float grid, sf::Vector2f position)
{
	this->initTile();
	this->shape.setPosition(position);
	this->shape.setSize(sf::Vector2f(grid, grid));
	this->shape.setFillColor(sf::Color::White);
	this->shape.setTexture(&tex);
}

Tile::~Tile()
{

}


void Tile::update(const float& deltaTime)
{

}

void Tile::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}