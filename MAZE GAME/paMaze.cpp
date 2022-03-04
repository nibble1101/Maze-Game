#include"paMaze.h"

Maze::Maze(RenderWindow *window)
{
    this->window = window;
    window->setKeyRepeatEnabled(false);
    
	cellWidth = 50;

    board = new Board(HEIGTH / cellWidth, WIDTH / cellWidth - 500 / cellWidth, cellWidth);

    time = new Text;
    gamePlayRules = new Text;
    fStart = new Text;
    giveUp = new Text;
    winningMessage = new Text;
    givenUp = new Text;

    clockFont = new Font;
    if (!clockFont->loadFromFile("JOKERMAN.ttf"))
    {
        exit(0);
    }
    float empty = WIDTH - 500;
    
    int a = 100;

   

    time->setCharacterSize(25);
    time->setString("PLEASE HIT ESCAPE KEY TO EXIT");
    time->setFillColor(Color::White);
    time->setPosition(Vector2f(empty - (time->getGlobalBounds().width)/2, 900 - 900*0.25));
    time->setStyle(Text::Bold | Text::Underlined);
    time->setFont(*clockFont);

    givenUp->setCharacterSize(25);
    givenUp->setString("IS IT TOO HARD FOR YOU?\n\nIT'S OKAY, TRY AGAIN LATER.\n\nPLEASE HIT ESCAPE TO EXIT");
    givenUp->setFillColor(Color::White);
    givenUp->setPosition(Vector2f(empty - (givenUp->getGlobalBounds().width) / 2, 900 * 0.5));
    givenUp->setStyle(Text::Bold | Text::Underlined);
    givenUp->setFont(*clockFont);
    
    winningMessage->setCharacterSize(25);
    winningMessage->setString("CONGRATULATIONS!!!\n\nYOU WON!!\n\nPLEASE HIT ESCAPE TO EXIT");
    winningMessage->setFillColor(Color::White);
    winningMessage->setPosition(Vector2f(empty - (winningMessage->getGlobalBounds().width) / 2, 900 *0.50));
    winningMessage->setStyle(Text::Bold | Text::Underlined);
    winningMessage->setFont(*clockFont);

    giveUp->setCharacterSize(25);
    giveUp->setString("HIT Q KEY TO GIVE UP");
    giveUp->setFillColor(Color::White);
    giveUp->setPosition(Vector2f(empty - (giveUp->getGlobalBounds().width) / 2, 900 *0.50));
    giveUp->setStyle(Text::Bold | Text::Underlined);
    giveUp->setFont(*clockFont);

    fStart->setCharacterSize(25);
    fStart->setString("HIT F KEY TO START");
    fStart->setFillColor(Color::White);
    fStart->setPosition(Vector2f(empty - (fStart->getGlobalBounds().width) / 2, 900 * 0.30));
    fStart->setStyle(Text::Bold | Text::Underlined);
    fStart->setFont(*clockFont);

    gamePlayRules->setCharacterSize(25);
    gamePlayRules->setString("USE ARROW KEYS TO MAKE THE \nSQUARE MOVE");
    gamePlayRules->setFillColor(Color::White);
    gamePlayRules->setPosition(Vector2f(empty - (gamePlayRules->getGlobalBounds().width) / 2, 900 * 0.10));
    gamePlayRules->setStyle(Text::Bold | Text::Underlined);
    gamePlayRules->setFont(*clockFont);
    

    EmptySpace = new RectangleShape;
    clockWall = new Texture;
    clockWall->setSmooth(true);

    clockWall->loadFromFile("BrickWall.png");
    EmptySpace->setSize(Vector2f(WIDTH,empty));
    EmptySpace->setTexture(clockWall);
    EmptySpace->setPosition(Vector2f(empty, 0));

}

void Maze::pollEvents()
{
    sf::Event evnt;
    while (window->pollEvent(evnt))
    {
        window->setKeyRepeatEnabled(false);
        if (evnt.type == sf::Event::Closed)
        {
            window->close();
        }
        if(Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window->close();
        if (evnt.type == sf::Event::KeyPressed)
        {
            if (evnt.key.code == sf::Keyboard::F)
            {
                timer = new Timer::Timer();
                startPathFinding = true;
            }
        }
    }
}

void Maze::run()
{
    //Clear -> update -> draw -> display -> poll events
    while (window->isOpen())
    {
        pollEvents();
        window->clear(Color::Cyan);
        update();
        window->display();
    }
}


void Maze::update()
{
    if (!board->isMazeGenerated)
        board->generateMaze();

    if (board->isMazeGenerated && startPathFinding && board->isPathFound == false)
    {
        board->playGame();
        sf::sleep(sf::milliseconds(120));
    }
    //std::cout << "\nDone";

    board->display(*window);
    window->draw(*EmptySpace);
    if (!board->isPathFound)
    {
        window->draw(*time);
        window->draw(*gamePlayRules);
        window->draw(*fStart);
        window->draw(*giveUp);
    }
    
    if (board->isPathFound && !board->isGivenUp)
    {
        window->draw(*winningMessage);
    }
    if (board->isGivenUp)
    {
        window->draw(*givenUp);
    }
}