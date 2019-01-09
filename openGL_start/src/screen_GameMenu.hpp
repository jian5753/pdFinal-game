#include <iostream>
#include <SFML/Graphics.hpp>
#include <Menu.h>

class screen_0 : public cScreen
{
private:
	/*game menu selection*/
	enum { play, option, exitGame };

public:
	screen_0(void);
	virtual int Run(sf::RenderWindow &window);
};

screen_0::screen_0(void)
{

}

int screen_0::Run(sf::RenderWindow &window)
{
	/*Game Menu*/
	Menu menu(window.getSize().x, window.getSize().y);
	menu.draw(window);
	window.display();

	sf::Event preparation;
	bool Running = true;
	while (Running)
	{
		//Verifying events
		while (window.pollEvent(preparation)) {
			switch (preparation.type)
			{
			if (preparation.type == sf::Event::Closed)
			{
				return (-1);
			}
			case sf::Event::KeyPressed:
				switch (preparation.key.code)
				{
				case sf::Keyboard::Up:
					menu.MoveUp();
					window.clear();
					menu.draw(window);
					window.display();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					window.clear();
					menu.draw(window);
					window.display();
					break;
				case sf::Keyboard::Enter:
					switch (menu.GetPressedItem())
					{
					case play:
						return (1);
						break;
					case option:
						break;
					case exitGame:
						return (-1); //notsure
						break;
					}
				}
			}
		}
	}

	//Never reaching this point normally, but just in case, exit the application
	return (-1);
}