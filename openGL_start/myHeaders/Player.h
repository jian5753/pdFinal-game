//play.h

#pragma once
#include <SFML/\Graphics.hpp>
#include <Animation.h>
#include <Collider.h>
using namespace sf;
class Player
{


public:
	RectangleShape body;

public:
	Player(Texture* texture, Vector2u imageCnt, float switchtime, bool backForthCycle, float speed, float jumpHeight);
	~Player();

	void Update(float deltaTime, FloatRect windowBounds);
	void Draw(RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	sf::Vector2f GetVelocity() { return velocity; }
	void SetVerticalVelocity(float y)
	{
		velocity.y = y;
	}
	void SetHorizontalPosition(float x);
	void SetVerticalPosition(float y);

	Vector2f getPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }


private:

	Animation animation;
	unsigned int row;
	float speed;
	float originalSpeed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canPull;
	float jumpHeight;
};

