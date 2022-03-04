#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Welcome
{

private:

	RectangleShape *backgroundRectangle;
	RenderWindow *window;
	RectangleShape *illuminati;
	Font *welcomeFont;
	Text *welcomeText;
	Text *enter, *esc;

public:

	Welcome();
	void draws();
	void decision(Event *evnt);
	void run();
		
};




#endif // !WELCOMEPAGE_H
