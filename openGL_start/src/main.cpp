#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
	RenderWindow window(VideoMode(1080, 480), "sfml window", Style::Close | Style::Resize);
	View view(Vector2f(0.0f, 0.0f), Vector2f(600.0f, 300.0f));

	/*declare texture and load file*/
	/*the sizr of player is define in player.cpp by default. no worry of setting size*/
	Texture firzenTexture;
	firzenTexture.loadFromFile("fighters/firzen/firzen.png");

	/*create player firzen*/
	Player firzen(&firzenTexture, Vector2u(4, 4), 0.3f, true, 100.0f);
	float deltaTime = 0.0f;

	/*create some platform to test*/
	Platform platform1(NULL, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(0.0f, 50.0f));

	/*timer to keep animation update*/
	Clock clock;

	while (window.isOpen()) {	 

		/*keep player, firzen update*/
		deltaTime = clock.restart().asSeconds();
		firzen.Update(deltaTime);
	
		platform1.GetCollider().CheckCollision(&firzen.GetCollider(), 0.0f);
		
		/*set some window shit including view*/
		view.setCenter(firzen.getPosition());	//need setCenter after calling player.update()
		window.clear(Color(150,150,150));
		//window.setView(view);

		/*draw the shit on the window*/
		firzen.Draw(window);
		platform1.Draw(window);

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

		if (Mouse::isButtonPressed(Mouse::Left)) {
			std::cout<<"hello\n";
		}
	}
}