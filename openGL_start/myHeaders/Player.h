#pragma once
#include <SFML/\Graphics.hpp>
#include <Animation.h>
#include <Collider.h>
using namespace sf;
class Player
{
public:
	Player(Texture* texture, Vector2u imageCnt, float switchtime, bool backForthCycle, float speed, float jumpHeight);
	~Player();

	void Update(float deltaTime);
	void Draw(RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	sf::Vector2f GetVelocity() { return velocity; }

	Vector2f getPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

public:
	RectangleShape body;

private:
	
	Animation animation;
	unsigned int row;
	float speed;
	float originalSpeed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;
};

