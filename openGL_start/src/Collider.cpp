#include "Collider.h"
#include <iostream>

Collider::Collider(sf::RectangleShape& body) :
	body(body)
{	 
}

Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider* other, float push, sf::Vector2f& direction)
{
	/*get shit we need*/
	sf::Vector2f otherPosition = other->GetPosition();
	sf::Vector2f otherHalfSize = other->GetHalfSize();
	sf::Vector2f thisPosition = this->GetPosition();
	sf::Vector2f thisrHalfSize = this->GetHalfSize();

	

	/*delta of two center*/
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	/*the intersect of two center*/
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisrHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisrHalfSize.y);

	/*some if else*/
	if (intersectX < 0.0f and intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);
		/*
		std::printf("delta X and deltaY (%f, %f)\n", deltaX, deltaY);
		std::printf("halfSize of player (%f, %f)\n", otherHalfSize.x, otherHalfSize.y);
		std::printf("halfSize of block (%f, %f)\n", thisrHalfSize.x, thisrHalfSize.y);
		std::printf("interxection (%f, %f)\n", intersectX, intersectY);*/

		if (intersectX > intersectY)
		{
			direction.y = 0.0f;
			if (deltaX > 0.0f)
			{	
				//std::cout << "git pushed from right \n";
				Move(intersectX * (1.0f - push), 0.0f);
				other->Move(-intersectX * push, 0.0f);
				direction.x = 1.0f;
				
			}
			else
			{
				//std::cout << "git pushed from left \n";
				Move(-intersectX * (1.0f - push), 0.0f);
				other->Move(intersectX * push, 0.0f);
				direction.x = -1.0f;
			}
		}
		else
		{
			direction.x = 0.0f;
			if (deltaY > 0.0f)
			{
				//std::cout << "git pushed from bottom \n";
				Move(0.0f, intersectY * (1.0f - push));
				other->Move(0.0f, -intersectY * push);
				direction.y = 1.0f;
			}
			else
			{	
				//std::cout << "git pushed from  top \n";
				Move(0.0f,-intersectY * (1.0f - push));
				other->Move(0.0f, intersectY * push);
				direction.y = -1.0f;
			}
		}
		return true;
	}
	return false;
}
