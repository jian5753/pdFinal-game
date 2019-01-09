#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Player.h>
#include <Collider.h>
#include <Platform.h>
#include <sstream>
#include <string>
using namespace sf;

static const float VIEW_HEIGHT = 300.0f;
const unsigned int WINDOW_WIDTH = 1080;
const unsigned int WINDOW_HEIGHT = 800;
const float PLATFORM_WIDTH = 150.0f;
const float PLATFORM_HEIGHT = 20.0f;
const float PLAYER_WIDTH = 120.0f;
const float PLAYER_HEIGHT = 160.0f;
const float PLAYER_JUMP = PLAYER_HEIGHT;

void ReSizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

const int platCnt = 18;
/*create a shit ton of platforms*/



int main(void)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("Dead Or Alive - You Spin Me Round (Like a Record) (online-audio-converter.com).wav"))
		return -1;
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.setVolume(30.f);
	sound.setLoop(true);

	sf::SoundBuffer startsound;
	if (!startsound.loadFromFile("The Voice  Chair choice button (sound effect)-[AudioTrimmer.com] (1).wav"))
		return -1;
	sf::Sound start;
	start.setBuffer(startsound);
	

	sf::Font font;
	if (!font.loadFromFile("OpenSans-SemiboldItalic.ttf"))
	{
		// error...
	}

	sf::Text text;
	text.setFont(font); // font is a sf::Font
	text.setCharacterSize(50); // in pixels, not points!
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(120, 5);

	sf::Text word;
	word.setFont(font); // font is a sf::Font
	word.setCharacterSize(40); // in pixels, not points!
	word.setFillColor(sf::Color::Black);
	word.setStyle(sf::Text::Bold);
	word.setPosition(13, 10);
	word.setString("score");

	// inside the main loop, between window.clear() and window.display()
	/*screen display shits*/
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Doodle", Style::Close | Style::Resize);
	sf::FloatRect windowBounds(sf::Vector2f(0.f, 0.f), window.getDefaultView().getSize());
	View view(Vector2f(0.0f, 0.0f), Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

	/*declare texture and load file*/
	/*the sizr of player is define in player.cpp by default. no worry of setting size*/
	Texture firzenTexture;
	firzenTexture.loadFromFile("fighters/firzen/firzen_noMargin.png");

	/*background image*/
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("fighters/background/bgg.jpg");


	/*create player firzen*/
	Player firzen(&firzenTexture, Vector2u(4, 4), 0.3f, true, 150.0f,150.0f);
	float deltaTime = 0.0f;
	
	Texture startTexture;
	startTexture.loadFromFile("fighters/start/startDark.png");

	Platform startImg(&startTexture, sf::Vector2f(364.0f, 61.0f), sf::Vector2f((WINDOW_WIDTH/2), 550.0f));

	Texture pfTexture;
	pfTexture.loadFromFile("fighters/background/platform.png");

	//ready to play

	while (true) {
		Event evnt;
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


//		std::printf("press space to start!");
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			start.play();
			break;
		}
		sound.play();
		/*draw*/
		sf::Sprite background(backgroundTexture);
		window.draw(background);
		startImg.Draw(window);
		window.display();
	}
	
	


	/*create some platform to test*/
	/* to Zi Shian
	To creat platforms you'll need a textrue pointer to set the texture of platform or leave it null to make it white as default.
	and you'll need two sf::vector2f to determin the size (first) and position(second).

	After finishing creating platform, remember to adjust the code in the "collision section" and "draw section" 
	so that the new platforms will work correctly.

	Also, there's a function of platform objects "setVerticalVelocity" (i wrote it in the platform.h)
	if you wanna make some platforms to fall.
	*/ 
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
		plats[i] = new Platform(&pfTexture, sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT), sf::Vector2f(positionX,positionY));
		lastPositionX = positionX;
		lastPositionY = positionY;
	}

	/*timer to keep animation update*/
	Clock clock;
	float opTime = 0.0f;
	const float OP_FREQ = 1.0f;

	/*variables to check collision between player and platforms*/
//	float deltaX, deltaY, intersectionX, intersectionY;

	while (window.isOpen()) {
		Event evnt;
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
			if(plats[i]->GetCollider().CheckCollision(&firzen.GetCollider(), 1.0f, direction))
				firzen.OnCollision(direction);
		}
		
		/*make platforms fall*/
		for (int i = 0; i < platCnt; i++)
		{
			plats[i]->setVerticalVelocity(0.3f);
			if (plats[i]->getPosition().y > WINDOW_HEIGHT) {
				std::printf("block # %i baba~\n",i);
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
				plats[i] = new Platform(&pfTexture, sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT), sf::Vector2f(positionX, positionY));
			}
		}

		/*set some window shit including view*/
		view.setCenter(WINDOW_WIDTH / 2, firzen.getPosition().y);	//need setCenter after calling player.update()
		window.clear(Color(150,150,150));
		window.setView(view);

		/*draw*/
		sf::Sprite background(backgroundTexture);
		background.setPosition(0, firzen.getPosition().y - WINDOW_HEIGHT/2);
		window.draw(background);
		
		platform1.Draw(window);
		for (int i = 0; i < platCnt; i++)
			plats[i]->Draw(window);
		firzen.Draw(window);
		/*some output*/
		opTime += deltaTime;
		// positive means upward
		if (opTime >= OP_FREQ )
		{
			opTime = 0.0f;
			std::printf("velocity :(%f, %f)\n", firzen.GetVelocity().x, -firzen.GetVelocity().y);
		}
		// set the string to display
		std::ostringstream oss;
		float score = 0;
		if ((WINDOW_HEIGHT - firzen.getPosition().y) / 10 > score)
		{
			score += ((WINDOW_HEIGHT - firzen.getPosition().y) / 10);
			oss << static_cast<int>(score);
			std::string str = oss.str();
			text.setString(str);
		}
		text.setPosition(120, 5 + firzen.getPosition().y - WINDOW_HEIGHT / 2);
		word.setPosition(13, 10 + firzen.getPosition().y - WINDOW_HEIGHT / 2);
		window.draw(text);
		window.draw(word);
		window.display();
	}
}