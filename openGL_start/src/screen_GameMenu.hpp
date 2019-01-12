#include <iostream>
#include <SFML/Graphics.hpp>
#include <Menu.h>
#include "cScreen.hpp"
#include <Platform.h>


class screen_0 : public cScreen
{
private:
	/*game menu selection*/
	enum { play, option, exitGame };
	
	sf::Texture startTexture;
	Platform startImg;
	const unsigned int WINDOW_WIDTH = 1080;

public:
	screen_0(void);
	virtual int Run(sf::RenderWindow &window);
};

screen_0::screen_0(void)
	:startImg(&startTexture, sf::Vector2f(364.0f, 61.0f), sf::Vector2f((WINDOW_WIDTH / 2), 550.0f))
{

}

int screen_0::Run(sf::RenderWindow &window)
{
	/*Game Menu*/
	startTexture.loadFromFile("fighters/start/startDark.png");
	

	Menu menu(window.getSize().x, window.getSize().y);
	menu.draw(window);
	startImg.Draw(window);

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
					startImg.Draw(window);

					window.display();
					break;
				case sf::Keyboard::Down:
					menu.MoveDown();
					window.clear();
					menu.draw(window);
					startImg.Draw(window);

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