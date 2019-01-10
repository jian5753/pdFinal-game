#include <SFML/Graphics.hpp>
#include "Screens.hpp"

using namespace sf;

const unsigned int WINDOW_WIDTH = 1080;
const unsigned int WINDOW_HEIGHT = 800;

int main(void)
{
	//Applications variables
	std::vector<cScreen*> Screens;
	int screen = 0;

	//Window creation
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Doodle", Style::Close | Style::Resize);

	//Mouse cursor no more visible
	//window.setMouseCursorVisible(false);

	//Screens preparations
	screen_0 s0;
	Screens.push_back(&s0);
	screen_1 s1;
	Screens.push_back(&s1);
	//Main loop
	while (screen >= 0)
	{
		screen = Screens[screen]->Run(window);
	}

	return EXIT_SUCCESS;	
	
	/*to Zi Shian    
	To creat platforms you'll need a textrue pointer to set the texture of platform or leave it null to make it white as default.
	and you'll need two sf::vector2f to determin the size (first) and position(second).

	After finishing creating platform, remember to adjust the code in the "collision section" and "draw section" 
	so that the new platforms will work correctly.

	Also, there's a function of platform objects "setVerticalVelocity" (i wrote it in the platform.h)
	if you wanna make some platforms to fall.

	lol funny stuff tho hahah so i leave it here
	*/ 
}