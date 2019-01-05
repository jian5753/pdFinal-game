#include "Player.h"
#include <iostream>




Player::Player(Texture* texture, Vector2u imageCnt, float switchtime, bool backForthCycle, float speed) : //consturct the attribute of player, animation
	animation(texture, imageCnt, switchtime, backForthCycle) //don't put semi column.
{
	this->speed = speed;
	this->originalSpeed = speed;
	row = 0;
	faceRight = true; 
	body.setPosition(500.0f, 280.0f);
	body.setSize(Vector2f(120.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
}


Player::~Player()
{
}

void Player::Draw(RenderWindow& window)
{
	window.draw(body);
}

void Player::Update(float deltaTime, FloatRect windowBounds)
{
	Vector2f movement(0.0f, 0.0f);
	bool moveOrIdle = true;
	bool run = false;

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		run = true;
		speed = originalSpeed * 2;
	}
	else {
		run = false;
		speed = originalSpeed;
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
		/*move left*/
		movement.x -= speed * deltaTime;

	if (Keyboard::isKeyPressed(Keyboard::D))
		/*move right*/
		movement.x += speed * deltaTime;

	if (Keyboard::isKeyPressed(Keyboard::S))
		/*move down*/
		movement.y += speed * deltaTime;

	if (Keyboard::isKeyPressed(Keyboard::W))
		/*move right*/
		movement.y -= speed * deltaTime;

	if (Keyboard::isKeyPressed(Keyboard::G))
		/*move right*/
		moveOrIdle = false;
		row = 2;
	
	if (moveOrIdle)
	{
		if (movement.x == 0.0f and movement.y == 0.0f)
		{
			row = 0;
		}
		else
		{
			if (run)
				row = 3;
			else
				row = 1;
			if (movement.x > 0.0f)
				faceRight = true;
			else
				faceRight = false;
			
		}
		
	}
	/*boundaries setting*/
	if (body.getPosition().x < windowBounds.left) {
		movement.x = windowBounds.left - body.getPosition().x;
	}
	if (body.getPosition().x > windowBounds.left + windowBounds.width) {
		movement.x = (windowBounds.left + windowBounds.width) - body.getPosition().x;
	}
	if (body.getPosition().y < windowBounds.top) {
		movement.y = windowBounds.top - body.getPosition().y;
	}
	if (body.getPosition().y > windowBounds.top + windowBounds.height) {
		movement.y = (windowBounds.top + windowBounds.height) - body.getPosition().y;
	}

	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}