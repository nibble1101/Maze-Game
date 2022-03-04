#ifndef PABOARD_H
#define PABOARD_H

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <stack>


#include"paCell.h"
#include"MinHeap.h"


class Board
{

private:

	int rows, columns;
	int cellWidth;
	int maxSize;
	
	//std::vector<Cell*> cells;
	std::stack<Cell*> cellStack;
	
	bool seed;

	
	vector<Cell*> *board;
	Texture* cellTexture;

	Cell* startingCell;
	Cell* targetCell;
	Cell* player;
	Cell* movePlayer;
	int iteratorIndex = 0;

	std::stack<Cell*> *path;
	
	
	

public:
	Board(int rows, int columns, int cellWidth);
	void display(RenderWindow& window);

	
	Cell* checkNeighbours(Cell* cell);
	int getIndex(int x, int y, int cols);

	void generateMaze();
	void removeWall(Cell* current, Cell* next);
	void resetGridState();

	bool isWallPresent(Cell* current, Cell* next);

	Cell* current;
	Cell* getNeighbour(Cell* cell, char move);



	bool isMazeGenerated;
	bool isPathFound;
	bool isGivenUp;
	bool isStarted;

	void playGame();
	void displayPath();

};
#endif // !PABOARD_H


