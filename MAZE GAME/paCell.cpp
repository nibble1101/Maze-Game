#include"paCell.h"


Cell::Cell()
{
	
}

Cell::Cell(int x, int y, int cellWidth)
{
	parent = nullptr;
	this->x = x;
	this->y = y;
	this->cellWidth = cellWidth;
	visited = false;

	right = true;
	top = true;
	bottom = true;
	left = true;


	float cellBorder = 5;

	leftWall = new RectangleShape;
	leftWall->setPosition(Vector2f(x * cellWidth, y * cellWidth));
	leftWall->setSize(Vector2f(cellWidth, cellBorder));
	leftWall->rotate(90);
	leftWall->setFillColor(Color::Black);


	rightWall = new RectangleShape;
	rightWall->setPosition(Vector2f(x * cellWidth + cellWidth, y * cellWidth));
	rightWall->setSize(Vector2f(cellWidth, cellBorder));
	rightWall->rotate(90);
	rightWall->setFillColor(Color::Black);

	topWall = new RectangleShape;
	topWall->setPosition(Vector2f(x * cellWidth, y * cellWidth));
	topWall->setSize(Vector2f(cellWidth, cellBorder));
	topWall->setFillColor(Color::Black);

	bottomWall = new RectangleShape;
	bottomWall->setPosition(Vector2f(x * cellWidth, y * cellWidth + cellWidth));
	bottomWall->setSize(Vector2f(cellWidth, cellBorder));
	bottomWall->setFillColor(Color::Black);

	cell = new RectangleShape;
	cell->setPosition(Vector2f(x * cellWidth, y * cellWidth));
	cell->setSize(Vector2f(cellWidth, cellWidth));

}

void Cell::draw(RenderWindow &window)
{
	window.draw(*cell);
	if (top)
		window.draw(*topWall);
	if (bottom)
		window.draw(*bottomWall);
	if (left)
		window.draw(*leftWall);
	if (right)
		window.draw(*rightWall);
}

void Cell::setState(State state)
{
	switch (state)
	{
	case State::Current:
		cell->setFillColor(sf::Color::Blue);
		break;

	case State::Visited:
		cell->setFillColor(sf::Color::Magenta);
		break;

	case State::Neutral:
		cell->setFillColor(sf::Color::White);
		break;

	case State::Start:
		cell->setFillColor(sf::Color::Green);
		break;

	case State::Target:
		cell->setFillColor(sf::Color::Red);
		break;

	case State::Path:
		cell->setFillColor(sf::Color::Cyan);
		break;

	default:
		break;
	}
}