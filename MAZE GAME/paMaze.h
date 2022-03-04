#ifndef PAMAZE_H
#define PAMAZE_H

#include"paBoard.h"
#include"Timer.h"

#define  WIDTH 1800
#define  HEIGTH 900

class Maze
{

private:

    RenderWindow* window;
    RectangleShape* EmptySpace;
    
    Board* board;
    int cellWidth;
    void pollEvents();
    void update();
    bool startPathFinding = false;
    bool isTimerDestroyed = false;


    Texture* clockWall;

    Text *time, *gamePlayRules, *fStart, *giveUp, *winningMessage, *givenUp;

    Font* clockFont;
  
    

public: 
    
    void run();
    Maze(RenderWindow *window);
    vector<Event> eventBuffer;
    Timer::Timer* timer;

};



#endif // !PAMAZE_H
