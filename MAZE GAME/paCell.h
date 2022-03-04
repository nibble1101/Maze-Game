#ifndef PACELL_H
#define PACELL_H

#include<SFML/Graphics.hpp>
#include<vector>

using namespace sf;
using namespace std;


enum class State
{
	Visited,
	Current,
	Neutral,
	Start,
	Target,
	Path
};

class Cell
{

public:


	int x, y;
	int cellWidth;

	bool left, right, top, bottom;
	bool visited;

	sf::RectangleShape* leftWall, * rightWall, * topWall, * bottomWall;
	sf::RectangleShape* cell;

	vector<Cell*> neighbours;
	Cell* parent;

	Cell(int x, int y, int cellWidth);
	Cell();

	void draw(RenderWindow& window);

	void setState(State state);

	



};

#endif // !PACELL_H



