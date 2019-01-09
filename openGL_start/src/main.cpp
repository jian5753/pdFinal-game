#include <SFML/Graphics.hpp>
#include <iostream>
#include <Player.h>
#include <Collider.h>
#include <Platform.h>
#include <cstdlib>
#include <ctime>
using namespace sf;

static const float VIEW_HEIGHT = 300.0f;

void ReSizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main(void)
{
	srand(static_cast <unsigned> (time(0)));
	/*screen display shits*/
	RenderWindow window(VideoMode(480, 700), "Doodle", Style::Close | Style::Resize);
	sf::FloatRect windowBounds(sf::Vector2f(0.f, 0.f), window.getDefaultView().getSize());
	View view(Vector2f(0.0f, 0.0f), Vector2f(720.0f, 360.0f));

	/*declare texture and load file*/
	/*the sizr of player is define in player.cpp by default. no worry of setting size*/
	Texture firzenTexture;
	firzenTexture.loadFromFile("fighters/firzen/firzen_noMargin.png");

	/*background image*/
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("fighters/background/bg.png");

	/*platform image*/
	Texture platformTexture;
	platformTexture.loadFromFile("fighters/Buttens and Headers/ButtonWide_GreenDark.png");


	/*create player firzen*/
	Player firzen(&firzenTexture, Vector2u(4, 4), 0.3f, true, 150.0f,150.0f);
	float deltaTime = 0.0f;

	/*create some platform to test*/
	Platform platform1(NULL, sf::Vector2f(1000000000000.0f, 1.0f), sf::Vector2f(0.0f, window.getDefaultView().getSize().y));
	Platform* randomPlatformList[16];
	int platformCount = 0;
	Platform platform(&platformTexture, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / window.getDefaultView().getSize().x)), static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / window.getDefaultView().getSize().y))));
	randomPlatformList[0] = &platform;
	platformCount++;
	Platform* tempPlatformPtr;
	while (true) {
		tempPlatformPtr = new Platform(&platformTexture, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / window.getDefaultView().getSize().x)), static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / window.getDefaultView().getSize().y))));
		for (int i = 0; i < platformCount; i++) {
			if (randomPlatformList[i]->getPosition().x - platform.getPosition().x < firzen.body.getSize().x * 1.5f) {
				if (randomPlatformList[i]->getPosition().y - platform.getPosition().y < firzen.body.getSize().y * 1.8f) {
					if (i + 1 == platformCount) {
						randomPlatformList[i + 1] = &platform;
						platformCount++;
						break;
					}
				}
				else {
					delete tempPlatformPtr;
					break;
				}
			}
			else{
					delete tempPlatformPtr;
					break;
				}
		}
		if (platformCount == 14) 
			break;
	}
	

	/*timer to keep animation update*/
	Clock clock;
	float opTime = 0.0f;
	const float OP_FREQ = 1.0f;

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

		/*collision*/
		sf::Vector2f direction;
		if (platform1.GetCollider().CheckCollision(&firzen.GetCollider(), 1.0f, direction)) {
			firzen.OnCollision(direction);
		}
		
		/*set some window shit including view*/
		view.setCenter(firzen.getPosition());	//need setCenter after calling player.update()
		window.clear(Color(150,150,150));
		//window.setView(view);

		/*draw the shit on the window*/
		sf::Sprite background(backgroundTexture);
		window.draw(background);
		firzen.Draw(window);
		platform1.Draw(window);
		for (int i = 0; i < 14; i++) 
			randomPlatformList[i]->Draw(window);
		

		/*some output*/
		opTime += deltaTime;
		if (opTime >= OP_FREQ )
		{
			opTime = 0.0f;
			std::printf("velocity :(%f, -%f)\n", firzen.GetVelocity().x, firzen.GetVelocity().y);
		}


		window.display();
	}
}