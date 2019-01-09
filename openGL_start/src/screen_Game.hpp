#include <iostream>
#include <Player.h>
#include <Collider.h>
#include <Platform.h>
#include <sstream>
#include <string>
#include "cScreen.hpp"
#include <SFML/Graphics.hpp>

class screen_1 : public cScreen
{
private:
	sf::Font font;
	sf::Text text;
	sf::Text word;

	/*declare texture and load file*/
	/*the sizr of player is define in player.cpp by default. no worry of setting size*/
	Texture firzenTexture;
	Texture backgroundTexture;
	
	sf::FloatRect windowBounds;
	
	sf::View view;

	/*timer to keep animation update*/
	Clock clock;
	float opTime;
	const float OP_FREQ = 1.0f;;

	/*group of consts*/
	const float VIEW_HEIGHT = 300.0f;  //***static prefix removed  
	const float PLATFORM_WIDTH = 150.0f;
	const float PLATFORM_HEIGHT = 20.0f;
	const float PLAYER_WIDTH = 120.0f;
	const float PLAYER_HEIGHT = 160.0f;
	const float PLAYER_JUMP = PLAYER_HEIGHT;
	const unsigned int WINDOW_WIDTH = 1080;
	const unsigned int WINDOW_HEIGHT = 800;
	const int platCnt = 18;

	void ReSizeView(const RenderWindow& window, View& view);
public:
	screen_1(void);
	virtual int Run(sf::RenderWindow &window);
};

screen_1::screen_1(void)
	:view(Vector2f(0.0f, 0.0f), Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)), windowBounds(sf::Vector2f(0.f, 0.f), sf::Vector2f((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT))
{
	if (!font.loadFromFile("OpenSans-SemiboldItalic.ttf"))
	{
		// error...
	}

	/*timer to keep animation update*/
	opTime = 0.0f;
}

/*helper func.*/
void screen_1::ReSizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int screen_1::Run(sf::RenderWindow &window)
{
	text.setFont(font); // font is a sf::Font
	text.setCharacterSize(50); // in pixels, not points!
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(120, 5);
	
	word.setFont(font); // font is a sf::Font
	word.setCharacterSize(40); // in pixels, not points!
	word.setFillColor(sf::Color::White);
	word.setStyle(sf::Text::Bold);
	word.setPosition(13, 10);
	word.setString("score");
	
	/*texture loading*/
	/*role image*/
	firzenTexture.loadFromFile("fighters/firzen/firzen_noMargin.png");
	/*background image*/
	backgroundTexture.loadFromFile("fighters/background/bg.jpg");
	
	/*create player firzen*/
	Player firzen(&firzenTexture, Vector2u(4, 4), 0.3f, true, 150.0f, 150.0f);
	float deltaTime = 0.0f;

	/*base Platform*/
	Platform platform1(NULL, sf::Vector2f(1000000000000.0f, 50.0f), sf::Vector2f(0.0f, 800.0f));

	/*create shit tons of platforms*/
	Platform** plats = new Platform*[platCnt];
	float positionX = 0.0f, positionY = 0.0f;
	float lastPositionX = WINDOW_WIDTH / 2, lastPositionY = WINDOW_HEIGHT;
	for (int i = 0; i < platCnt; i++)
	{
		if (rand() % 2000 <= 1000)
		{
			positionX = (float)WINDOW_WIDTH / 2 + rand() % 300;
			std::cout << "right\n";
		}
		else
		{
			positionX = (float)WINDOW_WIDTH / 2 - rand() % 300;
			std::cout << "left\n";
		}
		positionY = lastPositionY - rand() % 20 - (float)(PLAYER_HEIGHT*0.5);
		plats[i] = new Platform(NULL, sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT), sf::Vector2f(positionX, positionY));
		lastPositionX = positionX;
		lastPositionY = positionY;
	}
	
	// before drawing, clean it 
	window.clear(sf::Color(0, 0, 0, 0));
	/*screen display shits*/
	/*draw background*/
	sf::Sprite background(backgroundTexture);
	window.draw(background);
	window.display();


	sf::Event evnt;
	bool Running = true;

	while (Running)
	{
		//Verifying events
		while (window.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case Event::Closed:
				window.close();
				break;

			case Event::Resized:
				ReSizeView(window, view);
				break;
			}
		}

		/*record the initial position*/
		Vector2f firzenLastTime = firzen.getPosition();
		Vector2f blockLastTime = platform1.getPosition();

		/*keep player, firzen update*/
		deltaTime = clock.restart().asSeconds();
		if (deltaTime >= 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
		firzen.Update(deltaTime, windowBounds);

		/*make platforms drop*/

		/*collision*/
		sf::Vector2f direction;
		if (platform1.GetCollider().CheckCollision(&firzen.GetCollider(), 1.0f, direction)) {
			firzen.OnCollision(direction);
		}
		for (int i = 0; i < platCnt; i++)
		{
			if (plats[i]->GetCollider().CheckCollision(&firzen.GetCollider(), 1.0f, direction))
				firzen.OnCollision(direction);
		}

		/*make platforms fall*/
		for (int i = 0; i < platCnt; i++)
		{
			plats[i]->setVerticalVelocity(0.3f);
			if (plats[i]->getPosition().y > WINDOW_HEIGHT) {
				std::printf("block # %i baba~\n", i);
				std::cout << "height : " << plats[i]->getPosition().y << std::endl;

				delete plats[i];
				if (rand() % 2000 <= 1000)
				{
					positionX = (float)WINDOW_WIDTH / 2 + rand() % 300;
				}
				else
				{
					positionX = (float)WINDOW_WIDTH / 2 - rand() % 300;
				}
				positionY = rand() % 2 - (float)WINDOW_HEIGHT;
				std::printf("new position (%f,%f)", positionX, positionY);
				//system("pause");
				plats[i] = new Platform(NULL, sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT), sf::Vector2f(positionX, positionY));
			}
		}
		/*set some window shit including view*/
		//view.setCenter(firzen.getPosition());	//need setCenter after calling player.update()
		window.clear(Color(150, 150, 150));
		//window.setView(view);

		/*draw*/
		sf::Sprite background(backgroundTexture);
		window.draw(background);

		platform1.Draw(window);
		for (int i = 0; i < platCnt; i++)
			plats[i]->Draw(window);
		firzen.Draw(window);
		/*some output*/
		opTime += deltaTime;
		// positive means upward
		if (opTime >= OP_FREQ)
		{
			opTime = 0.0f;
			std::printf("velocity :(%f, %f)\n", firzen.GetVelocity().x, -firzen.GetVelocity().y);
		}
		// set the string to display
		std::ostringstream oss;
		float score = ((WINDOW_HEIGHT - firzen.getPosition().y));
		oss << static_cast<int>(score);
		std::string str = oss.str();
		text.setString(str);
		window.draw(text);
		window.draw(word);
		window.display();
	}

	//Never reaching this point normally, but just in case, exit the application
	return -1;
}