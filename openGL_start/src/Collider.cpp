#include "Collider.h"
#include <iostream>


Collider::Collider(sf::RectangleShape& body) :
	body(body)
{	 
}

Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider* other, float push)
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
		push = std::min(std::max(push, 0.0f), 1.0f);   //

		//choose smaller to push
		if (intersectX > intersectY) // abs(intersectX) < abs(intersectY) cuz using the negative #
		{
			if (deltaX > 0.0f)
			{	
				std::cout << "pushing align x \n";
				Move(intersectX * (1.0f - push), 0.0f);
				other->Move(-intersectX * push, 0.0f);
			}
			else
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other->Move(intersectX * push, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - push));
				other->Move(0.0f, -intersectY * push);
			}
			else
			{
				Move(0.0f,-intersectY * (1.0f - push));
				other->Move(0.0f, intersectY * push);
			}
		}
		return true;
	}
	return false;
}
