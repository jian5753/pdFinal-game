#include <SFML/Graphics.hpp>
#include <iostream>
#include <Player.h>
#include <Collider.h>
#include <Platform.h>
using namespace sf;

static const float VIEW_HEIGHT = 300.0f;
const float WINDOW_WIDTH = 1080.0f;
const float WINDOW_HEIGHT = 800.0f;
const float PLATFORM_WIDTH = 150.0f;
const float PLATFORM_HEIGHT = 20.0f;
const float PLAYER_WIDTH = 120.0f;
const float PLAYER_HEIGHT = 150.0f;
const float PLAYER_JUMP = PLAYER_HEIGHT;

void ReSizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main(void)
{
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
	backgroundTexture.loadFromFile("fighters/background/bg.jpg");


	/*create player firzen*/
	Player firzen(&firzenTexture, Vector2u(4, 4), 0.3f, true, 150.0f,150.0f);
	float deltaTime = 0.0f;

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
	Platform platform2(NULL, sf::Vector2f(PLATFORM_WIDTH, PLATFORM_HEIGHT), sf::Vector2f(200.0f, 700.0f));
	

	/*timer to keep animation update*/
	Clock clock;
	float opTime = 0.0f;
	const float OP_FREQ = 1.0f;

	/*variables to check collision between player and platforms*/
	float deltaX, deltaY, intersectionX, intersectionY;

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

		deltaX = abs(platform2.getPosition().x - firzen.getPosition().x);
		deltaY = abs(platform2.getPosition().y - firzen.getPosition().y);
		intersectionX = deltaX - (PLAYER_WIDTH / 2 + PLATFORM_WIDTH / 2);
		intersectionY = deltaY - (PLAYER_HEIGHT / 2 + PLATFORM_HEIGHT / 2);
		if (intersectionY <= 0 && intersectionX <= 0)
		{
			firzen.SetVerticalVelocity(-sqrt(2.0f * 981.0f * PLAYER_JUMP));
		}


		/*set some window shit including view*/
		//view.setCenter(firzen.getPosition());	//need setCenter after calling player.update()
		window.clear(Color(150,150,150));
		//window.setView(view);

		/*draw*/
		sf::Sprite background(backgroundTexture);
		window.draw(background);
		firzen.Draw(window);
		platform1.Draw(window);
		platform2.Draw(window);

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