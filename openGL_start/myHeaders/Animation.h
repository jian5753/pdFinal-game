#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
	/*functions*/
public:
	Animation(Texture* texture, Vector2u imageCnt, float switchtime, bool);
	~Animation();

	void update(int row, float deltaTime, bool faceRight);

private:

	/*variables*/
public:
	IntRect uvRect;

private:
	Vector2u imageCnt;
	Vector2u currentImg;
	bool backForthCycle;
	bool backing;
	bool heading;

	float totalTime;
	float switchTime;
};

