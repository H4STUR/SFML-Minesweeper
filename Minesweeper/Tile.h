#ifndef _TILE
#define _TILE

#include "stdafx.h"

enum tileType
{
	empty = 0,
	full = 9,
	flag,
	bomb
};
class Tile
{
public:
	Tile();
	Tile(float grid, sf::Vector2f position, short type = 0);
	~Tile();

	//Accessors
	const short getType() const;

	//Setters
	void setBomb();

	
	//functions
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target);

private:

	sf::RectangleShape shape;
	sf::Texture tex;

	short type;
	bool bomb;
	//Inits
	void initTile();

};

#endif //!_TILE