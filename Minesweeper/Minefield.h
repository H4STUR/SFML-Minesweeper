#ifndef _MINEFIELD
#define _MINEFIELD

#include "stdafx.h"
#include "Tile.h"

class Tile;

class Minefield
{
public:
	Minefield(float grid, sf::Vector2i& size, sf::Vector2f& position, unsigned short bombAmount = 10);
	~Minefield();

	//Accessors
	const bool contains(sf::Vector2f& point) const;

	//Gameplay Functions
	void setFlag(int x, int y);
	void openTile(int x, int y);

	void generateBombs();

	void openEmptyField(sf::Vector2i pos);

	void update(const float& deltaTime);
	const void render(sf::RenderTarget* target);

private:
	//Variables
	int layers;
	float grid;
	unsigned short bombAmount;
	bool areBombGenerated;

	sf::Vector2i size;
	sf::Vector2f position;
	sf::RectangleShape selector;
	sf::RectangleShape background;
	std::vector < std::vector< std::stack<Tile*> > >field;

	//functions
	const bool canBeOpened(sf::Vector2f pos) const;
	void clear();

	//Inits
	void reserveField();
	void initBackground();
};

#endif // !_MINEFIELD