#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Player.h>
#include <Collider.h>
#include <Platform.h>
using namespace sf;

static const float VIEW_HEIGHT = 300.0f;
const unsigned int WINDOW_WIDTH = 1080;
const unsigned int WINDOW_HEIGHT = 800;
const float PLATFORM_WIDTH = 150.0f;
const float PLATFORM_HEIGHT = 20.0f;
const float PLAYER_WIDTH = 120.0f;
const float PLAYER_HEIGHT = 160.0f;
const float PLAYER_JUMP = 165.0f;

void ReSizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

/*create shit tons of platforms*/
const int platCnt = 18;

int main(void)
{
	/*screen display shits*/
	RenderWindow window(VideoMode(1080, 720), "Doodle", Style::Close | Style::Resize);
	sf::FloatRect windowBounds(sf::Vector2f(0.f, 0.f), window.getDefaultView().getSize());
	View view(Vector2f(0.0f, 0.0f), Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

	/*declare texture and load file*/
	/*the sizr of player is define in player.cpp by default. no worry of setting size*/
	Texture firzenTexture;

	firzenTexture.loadFromFile("fighters/firzen/firzen_noMargin.png");

	/*background image*/
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("fighters/background/bg.jpg");

	/*platform image*/
	Texture platformTexture;
	platformTexture.loadFromFile("fighters/Buttens and Headers/ButtonWide_GreenDark.png");


	/*create player firzen*/
	Player firzen(&firzenTexture, Vector2u(4, 4), 0.3f, true, 150.0f, PLAYER_JUMP);
	float deltaTime = 0.0f;

	/*create some platform to test*/
	Platform platform1(NULL, sf::Vector2f(1000000000000.0f, 50.0f), sf::Vector2f(0.0f, 300.0f));
	Platform platform2(NULL, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(200.0f, 150.0f));

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
			if (plats[i]->GetCollider().CheckCollision(&firzen.GetCollider(), 1.0f, direction))
			{
				firzen.OnCollision(direction);
				if (firzen.GetVelocity().y > 0)
				{
					StartToRecordScore = true;
					platform1.SetVerticalPosition(platform1.getPosition().y + WINDOW_HEIGHT);
				}
			}
		}
		
		if (platform2.GetCollider().CheckCollision(&firzen.GetCollider(), 1.0f, direction))
		{
			firzen.OnCollision(direction);
		}
		
		/*set some window shit including view*/
		view.setCenter(WINDOW_WIDTH / 2, firzen.getPosition().y);	//need setCenter after calling player.update()
		window.clear(Color(150,150,150));
		//window.setView(view);

		/*draw*/
		sf::Sprite background(backgroundTexture);
		if (firzen.getPosition().y < WINDOW_HEIGHT / 2)
		{
			background.setPosition(0, firzen.getPosition().y - WINDOW_HEIGHT / 2);
		}
		window.draw(background);
		
		platform1.Draw(window);
		for (int i = 0; i < platCnt; i++)
			plats[i]->Draw(window);
		firzen.Draw(window);
		platform1.Draw(window);
		platform2.Draw(window);

		/*some output*/
		opTime += deltaTime;
		// positive means upward
		if (opTime >= OP_FREQ )
		{
			opTime = 0.0f;
			std::printf("velocity :(%f, %f)\n", firzen.GetVelocity().x, -firzen.GetVelocity().y);
		}
		
		
		//GameOver
		 if (firzen.getPosition().y > WINDOW_HEIGHT + 1)
  {
   gameoversound.setVolume(30.0f);
   if (havePlayedSound == false)
   {
    sound.stop();
    gameoversound.play();
   }
   havePlayedSound = true;
   gameovertext.setPosition(300, 300);
   window.draw(gameovertext);
   //system("pause");
  }
		//window.draw(gameovertext);
		// set the string to display
		std::ostringstream oss;
		totalTime += deltaTime*10;
		tempScore = (WINDOW_HEIGHT - firzen.getPosition().y) / 10 + totalTime;
		if (tempScore > score && StartToRecordScore == true)
		{
			score = tempScore;
		}
		oss << static_cast<int>(score);
		std::string str = oss.str();
		text.setString(str);
		if (firzen.getPosition().y < WINDOW_HEIGHT / 2)
		{
			text.setPosition(121, 5 + firzen.getPosition().y - WINDOW_HEIGHT / 2);
			word.setPosition(13, 10 + firzen.getPosition().y - WINDOW_HEIGHT / 2);
		}
		
		window.draw(text);
		window.draw(word);
		window.display();
	}
}