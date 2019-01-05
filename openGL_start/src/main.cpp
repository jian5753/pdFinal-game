#include <SFML/Graphics.hpp>
#include <iostream>
#include <Player.h>
#include <Collider.h>
#include <Platform.h>
using namespace sf;

static const float VIEW_HEIGHT = 300.0f;

void ReSizeView(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main(void)
{
	/*screen display shits*/
	RenderWindow window(VideoMode(680, 800), "sfml window", Style::Close | Style::Resize);
	View view(Vector2f(0.0f, 0.0f), Vector2f(680.0f, 800.0f));

	/*declare texture and load file*/
	/*the sizr of player is define in player.cpp by default. no worry of setting size*/
	Texture firzenTexture;
	firzenTexture.loadFromFile("fighters/firzen/firzen_noMargin.png");

	/*create player firzen*/
	Player firzen(&firzenTexture, Vector2u(4, 4), 0.3f, true, 150.0f,150.0f);
	float deltaTime = 0.0f;

	/*create some platform to test*/
	Platform platform1(NULL, sf::Vector2f(1000000000000.0f, 50.0f), sf::Vector2f(0.0f, 300.0f));
	Platform platform2(NULL, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(200.0f, 150.0f));

	/*timer to keep animation update*/
	Clock clock;
	float opTime = 0.0f;
	const float OP_FREQ = 1.0f;

	while (window.isOpen()) {

		/*record the initial position*/
		Vector2f firzenLastTime = firzen.getPosition();
		Vector2f blockLastTime = platform1.getPosition();

		/*keep player, firzen update*/
		deltaTime = clock.restart().asSeconds();
		if (deltaTime >= 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
		firzen.Update(deltaTime);

		/*collision*/
		sf::Vector2f direction;
		if (platform1.GetCollider().CheckCollision(&firzen.GetCollider(), 1.0f, direction)) {
			firzen.OnCollision(direction);
		}
		
		if (platform2.GetCollider().CheckCollision(&firzen.GetCollider(), 1.0f, direction))
		{
			firzen.OnCollision(direction);
		}
		
		/*set some window shit including view*/
		view.setCenter(firzen.getPosition());	//need setCenter after calling player.update()
		window.clear(Color(150,150,150));
		window.setView(view);

		/*draw the shit on the window*/
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
	}
}