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
	Tile(tileType type);
	Tile(float grid, sf::Vector2f position, tileType type = tileType::empty);
	~Tile();

	//Accessors
	const short getType() const;
	const unsigned short getAmountOfNeighborBombs() const;

	//Setters
	void setBomb();
	inline void incrementAmountOfNeighborBombs() { this->neighborBombAmount++; };

	
	//functions
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target);

private:

	sf::RectangleShape shape;
	sf::Texture tex;
	unsigned short neighborBombAmount;

	tileType type;
	bool bomb;
	//Inits
	void setType(tileType type);

};

#endif //!_TILE