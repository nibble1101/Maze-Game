#include"paBoard.h"



Board::Board(int rows, int columns, int cellWidth)
{
    isStarted = false;
    isMazeGenerated = false;
    isPathFound = false;
    isGivenUp = false;
    isStarted = false;

    this->cellWidth = cellWidth;
    this->columns = columns;
    this->rows = rows;
    maxSize = rows * columns;
    board = new vector<Cell*>;
    path = new stack<Cell*>;
    seed = false;


    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            board->push_back(new Cell(x, y, cellWidth));
        }
    }

    current = (*board)[getIndex(0, 0, columns)]; //Top Left
    current->visited = true;
    current->setState(State::Current);

    startingCell = (*board)[getIndex(0, 0, columns)];
    player = startingCell;
    targetCell = (*board)[getIndex(columns - 1, rows - 1, columns)];


    cellTexture = new Texture;
    cellTexture->loadFromFile("Cell.png");

}


void Board::generateMaze()
{
    Cell* neighbor = checkNeighbours(current);

    if (neighbor != NULL)
    {
        neighbor->visited = true;
        neighbor->setState(State::Visited);

        cellStack.push(current);
        //Remove walls
        removeWall(current, neighbor);

        current->setState(State::Visited);
        current = neighbor;
        current->setState(State::Current);
        if (current == targetCell)
            *path = cellStack;
    }
    else if (cellStack.size() > 0)
    {
        Cell* cell = cellStack.top();
        cellStack.pop();
        current = cell;
        current->setState(State::Current);
    }
    else
    {
        isMazeGenerated = true;
        resetGridState();
    }
}

void Board::display(RenderWindow& window)
{
    for (int i = 0; i < board->size(); i++)
    {
        (*board)[i]->cell->setTexture(cellTexture);
        (*board)[i]->draw(window);
    }
}


Cell* Board::checkNeighbours(Cell* cell)
{
    std::vector<Cell*> neighbors;
        
    int x = cell->x;
    int y = cell->y;

    if (x >= 0 && x < columns && y - 1 >= 0 && y - 1 < rows) {
        Cell* top = (*board)[getIndex(x, y - 1, columns)];
        if (!top->visited)
            neighbors.push_back(top);
    }

    if (x + 1 >= 0 && x + 1 < columns && y >= 0 && y < rows) {
        Cell* right = (*board)[getIndex(x + 1, y, columns)];
        if (!right->visited)
            neighbors.push_back(right);
    }


    if (x >= 0 && x < columns && y + 1 >= 0 && y + 1 < rows) {
        Cell* bottom = (*board)[getIndex(x, y + 1, columns)];
        if (!bottom->visited)
            neighbors.push_back(bottom);
    }

    if (x - 1 >= 0 && x - 1 < columns && y >= 0 && y < rows) {
        Cell* left = (*board)[getIndex(x - 1, y, columns)];
        if (!left->visited)
            neighbors.push_back(left);
    }

    if (neighbors.size() > 0)
    {
        if (seed == false)
        {
            srand((unsigned int)time(NULL));
            seed = true;
        }
        int result = (rand() % neighbors.size());
        return neighbors[result];
    }
    else
        return NULL;
}

Cell* Board::getNeighbour(Cell* current, char move)
{
    int x = current->x;
    int y = current->y;

    if (move == 'T')
    {
        if (x >= 0 && x < columns && y - 1 >= 0 && y - 1 < rows)
        {
            Cell* top = (*board)[getIndex(x, y - 1, columns)];
            if (!isWallPresent(current, top))
                return top;
            else
                return nullptr;
        }
        return nullptr;
    }
    
    if (move == 'R')
    {
        if (x + 1 >= 0 && x + 1 < columns && y >= 0 && y < rows) {
            Cell* right = (*board)[getIndex(x + 1, y, columns)];
            if (!isWallPresent(current, right))
                return right;
            else
                return nullptr;
        }
        return nullptr;
    }
    

    if (move == 'B')
    {
        if (x >= 0 && x < columns && y + 1 >= 0 && y + 1 < rows) {
            Cell* bottom = (*board)[getIndex(x, y + 1, columns)];
            if (!isWallPresent(current, bottom))
                return bottom;
            else
                return nullptr;
        }
        return nullptr;
    }
 
    if (move == 'L')
    {
        if (x - 1 >= 0 && x - 1 < columns && y >= 0 && y < rows) 
        {
            Cell* left = (*board)[getIndex(x - 1, y, columns)];
            if (!isWallPresent(current, left))
                return left;
            else
                return nullptr;
        }
        return nullptr;
    }
    else
        return nullptr;

}

int Board::getIndex(int x, int y, int cols)
{
    return y * cols + x;
}


void Board::resetGridState()
{
    for (int i = 0; i < (*board).size(); i++)
    {
        (*board)[i]->setState(State::Neutral);
    }
}



void Board::removeWall(Cell* current, Cell* next)
{
    int x = current->x - next->x;
    int y = current->y - next->y;

    if (x == 1)
    {
        current->left = false;
        next->right = false;
        current->neighbours.push_back(next);
        next->neighbours.push_back(current);
    }
    else if (x == -1)
    {
        current->right = false;
        next->left = false;
        current->neighbours.push_back(next);
        next->neighbours.push_back(current);
    }

    if (y == 1)
    {
        current->top = false;
        next->bottom = false;
        current->neighbours.push_back(next);
        next->neighbours.push_back(current);
    }
    else if (y == -1)
    {
        current->bottom = false;
        next->top = false;
        current->neighbours.push_back(next);
        next->neighbours.push_back(current);
    }
}

bool Board::isWallPresent(Cell* current, Cell* next)
{
    int x = current->x - next->x;
    int y = current->y - next->y;

    if (x == 1) // Left Neighbour
    {
        if (current->left == false && next->right == false)
            return false;
    }
    else if (x == -1) // Right Neighbour
    {
        if (current->right == false && next->left == false)
            return false;
    }

    if (y == 1) //Top Neighbour
    {
        if (current->top == false && next->bottom == false)
            return false;
    }
    else if (y == -1) //Bottom Neighbour
    {
        if (current->bottom == false && next->top == false)
            return false;
    }
    return true;
}

void Board::playGame()
{
   
    if (!isStarted)
    {
        startingCell->setState(State::Start);
        targetCell->setState(State::Target);
        isStarted = true;
    }
    
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
            std::cout << "\nUp Key";
            movePlayer = getNeighbour(player, 'T');
            if (movePlayer != nullptr)
            {
                player->setState(State::Neutral);
                player = movePlayer;
                player->setState(State::Current);
                if (player == targetCell)
                {
                    isPathFound = true;
                    player->setState(State::Start);
                }
               
            }
        
    }
    
 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        movePlayer = getNeighbour(player, 'B');
        if (movePlayer != nullptr)
        {
            player->setState(State::Neutral);
            player = movePlayer;
            player->setState(State::Current);
            if (player == targetCell)
            {
                isPathFound = true;
                player->setState(State::Start);
            }
        }
        
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        movePlayer = getNeighbour(player, 'L');
        if (movePlayer != nullptr)
        {
            player->setState(State::Neutral);
            player = movePlayer;
            player->setState(State::Current);
            if (player == targetCell)
            {
                isPathFound = true;
                player->setState(State::Start);
            }
        }
        
    }
 

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        
        movePlayer = getNeighbour(player, 'R');
        if (movePlayer != nullptr)
        {
            player->setState(State::Neutral);
            player = movePlayer;
            player->setState(State::Current);
            if (player == targetCell)
            {
                isPathFound = true;
                player->setState(State::Start);
            }
        }
        
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
    {
        isGivenUp = true;
        isPathFound = true;
        displayPath();
    }
    
}

void Board::displayPath()
{
    Cell* current = nullptr;
    while (path->size() != 0)
    {
        current = path->top();
        current->setState(State::Start);
        path->pop();
    }
}