#ifndef _TILE
#define _TILE

#include "stdafx.h"

class Tile
{
public:
	Tile();
	Tile(float grid, sf::Vector2f position);
	~Tile();

	//Accessors

	//functions
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target);

private:

	sf::RectangleShape shape;
	sf::Texture tex;

	//Inits
	void initTile();

};

#endif //!_TILE