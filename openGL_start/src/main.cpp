#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Player.h>
using namespace sf;


int main(void)
{
	RenderWindow window(VideoMode(1080, 480), "sfml window", Style::Close | Style::Resize);
	RectangleShape julian(Vector2f(120.0f,150.0f));
	julian.setOrigin(50.0f, 50.0f);
	julian.setPosition(106.0f, 106.0f);

	/*declare texture and load file*/
	/*the sizr of player is define in player.cpp by default. no worry of setting size*/
	Texture firzenTexture;
	firzenTexture.loadFromFile("fighters/firzen/firzen.png");

	/*animation declare*/
	Player firzen(&firzenTexture, Vector2u(4, 4), 0.3f, true, 100.0f);
	float deltaTime = 0.0f;
	Clock clock;

	while (window.isOpen()) {	 

		deltaTime = clock.restart().asSeconds();
		firzen.Update(deltaTime);

		/*animation activate*/

		window.clear(Color(150,150,150));
		firzen.Draw(window);
		window.display();

		Event evnt;

		while (window.pollEvent(evnt)) {
			switch (evnt.type) 
			{
			case Event::Closed:
				window.close();
				break;

			case Event::Resized:
				break;
			}
	
		}
	}
}