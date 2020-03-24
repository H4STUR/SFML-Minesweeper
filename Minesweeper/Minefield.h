#ifndef _MINEFIELD
#define _MINEFIELD

#include "stdafx.h"
#include "Tile.h"

class Tile;

class Minefield
{
public:
	Minefield(float grid, sf::Vector2i& size, sf::Vector2f& position);
	~Minefield();

	//Functions
	void setFlag();
	void openTile();

	//void updateGui(const float& deltaTime);
	void update(const float& deltaTime);
	const void render(sf::RenderTarget* target);

private:
	//Variables
	int layers;
	sf::Vector2i size;
	sf::Vector2f position;
	sf::RectangleShape selector;
	std::vector < std::vector< std::vector<Tile*> > >field;
	float grid;

	//functions
	void clear();

	//Inits
	void initField();

};

#endif // !_MINEFIELD