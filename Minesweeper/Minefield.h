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
	
	//Accessors
	const bool contains(sf::Vector2f& point) const;

	//Functions
	void setFlag(int x, int y);
	void openTile(int x, int y);

	//void updateGui(const float& deltaTime);
	void update(const float& deltaTime);
	const void render(sf::RenderTarget* target);

private:
	//Variables
	int layers;
	sf::Vector2i size;
	sf::Vector2f position;
	sf::RectangleShape selector;
	sf::RectangleShape background;
	std::vector < std::vector< std::stack<Tile*> > >field;
	float grid;

	//functions
	void clear();

	//Inits
	void initField();
	void initBackground();
};

#endif // !_MINEFIELD