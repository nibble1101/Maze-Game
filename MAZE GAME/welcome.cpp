#include"WelcomePage.h"
#include"paMaze.h"


Welcome::Welcome()
{
    //WINDOW CREATION
    window = new RenderWindow;
    window->create(VideoMode(1800, 900), "MAZE GAME", Style::Default);
    window->setKeyRepeatEnabled(false);

    //BACKGROUND FRAME
    backgroundRectangle = new RectangleShape;
    backgroundRectangle->setSize(Vector2f(window->getSize()));
    Texture *backgroundTexture;
    backgroundTexture = new Texture;
    if (!backgroundTexture->loadFromFile("Background.png"))
    {
        exit(0);
    }
    backgroundTexture->setSmooth(true);
    backgroundRectangle->setTexture(backgroundTexture);

    //ILUMINATI LOGO
    illuminati = new RectangleShape;
    illuminati->setSize(Vector2f(800.f, 800.f));
    
    Texture *logo;
    logo = new Texture;
    if (!logo->loadFromFile("illuminati.png"))
    {
        exit(0);
    }
    logo->setSmooth(true);
    illuminati->setTexture(logo);
    illuminati->setPosition(Vector2f(backgroundRectangle->getSize().x / 2 - illuminati->getSize().x / 2, backgroundRectangle->getSize().y / 2 - illuminati->getSize().y / 2));


    //Font
    welcomeFont = new Font;
    if (!welcomeFont->loadFromFile("JOKERMAN.ttf"))
    {
        exit(0);
    }


    //Welcome Text
   
    welcomeText = new Text;
    welcomeText->setFont(*welcomeFont);
    welcomeText->setString("WELCOME TO THE MAZE GAME ");
    welcomeText->setCharacterSize(70);
    welcomeText->setStyle(Text::Bold | Text::Underlined);
    welcomeText->setPosition(Vector2f(backgroundRectangle->getSize().x / 2 - welcomeText->getGlobalBounds().width / 2, 30.f));

    //Press Key Text(ESCAPE)
    enter = new Text;
    enter->setFont(*welcomeFont);
    enter->setString("HIT ESCAPE KEY TO EXIT ");
    enter->setCharacterSize(35);
    enter->setStyle(Text::Italic | Text::Bold);
    enter->setPosition(Vector2f(10.f, backgroundRectangle->getSize().y - 100.f));

    //Press Key Text(ENTER)
    esc = new Text;
    esc->setFont(*welcomeFont);
    esc->setString("HIT ENTER KEY TO CONTINUE ");
    esc->setCharacterSize(35);
    esc->setStyle(Text::Italic | Text::Bold);
    esc->setPosition(Vector2f(backgroundRectangle->getSize().x - esc->getGlobalBounds().width - 10.f, backgroundRectangle->getSize().y - 100.f));



}
void Welcome::draws()
{
	window->draw(*backgroundRectangle);
    window->draw(*welcomeText);
    window->draw(*illuminati);
    window->draw(*enter);
    window->draw(*esc);
}
void Welcome::decision(Event *evnt)
{
    if (evnt->type == Event::Closed)
        window->close();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        //window->close();
        Maze maze(window);
        maze.run();
    }
}

void Welcome::run()
{
    while (window->isOpen())
    {
        Event *evnt;
        evnt = new Event;
        while (window->pollEvent(*evnt))
        {
            decision(evnt);
        }

        //Update


        window->clear();

        //Draw

        draws();

        //Display

        window->display();
    }
}