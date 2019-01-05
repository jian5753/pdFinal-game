#include "Animation.h"
#include <iostream>



Animation::Animation(Texture* texture, Vector2u imageCnt, float switchtime, bool backForthCycle) {
	this->imageCnt = imageCnt;
	this->switchTime = switchtime;
	this->backForthCycle = backForthCycle;
	heading = true;
	backing = false;
	totalTime = 0.0f;
	currentImg.x = 0;

	uvRect.width = texture->getSize().x / float(imageCnt.x);
	uvRect.height = texture->getSize().y / float(imageCnt.y);
}

Animation::~Animation()
{
}

void Animation::update(int row, float deltaTime, bool faceRight)
{
	currentImg.y = row;
	if (row == 3)
	{
		totalTime += deltaTime * 2;
		backForthCycle = false;
		imageCnt.x = 3;
	}
	else
	{
		totalTime += deltaTime;
		imageCnt.x = 4;
	}
	if (row == 0 or row == 1 or row ==3 ) /* move or idle*/
	{
		if (totalTime >= switchTime)
		{
			totalTime -= switchTime;
			if (backForthCycle) {
				if (heading)
				{
					currentImg.x++;
					if (currentImg.x >= imageCnt.x)
					{
						currentImg.x = imageCnt.x - 1;
						backing = true;
						heading = false;
					}
				}	
				else if (backing) {
					currentImg.x--;
					if (currentImg.x < 0 or currentImg.x > imageCnt.x)
					{
						currentImg.x = 1;
						backing = false;
						heading = true;
					}
				}

			}
			else
			{
				currentImg.x++;
				if (currentImg.x >= imageCnt.x)
				{
					currentImg.x = 0;
				}
			}
		}
	}
	else if (row ==2 ) /*attact*/
	{
		if (totalTime >= switchTime / 2) {
			totalTime -= switchTime / 2;
			currentImg.x++;

			if (currentImg.x >= imageCnt.x) {
				row = 1;
				currentImg.x = 0;
			}
		}
	}

	uvRect.top = currentImg.y*uvRect.height;
	if (faceRight)
	{
		uvRect.left = currentImg.x * abs(uvRect.width);
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImg.x + 1)*abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
	
}
