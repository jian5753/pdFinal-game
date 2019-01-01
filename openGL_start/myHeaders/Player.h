#pragma once
#include <SFML/\Graphics.hpp>
#include <Animation.h>
using namespace sf;
class Player
{
public:
	Player(Texture* texture, Vector2u imageCnt, float switchtime, bool backForthCycle, float speed);
	~Player();

	void Update(float deltaTime);
	void Draw(RenderWindow& window);

private:
	RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	float originalSpeed;
	bool faceRight;

};

