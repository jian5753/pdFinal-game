#include "Player.h"
#include <iostream>




Player::Player(Texture* texture, Vector2u imageCnt, float switchtime, bool backForthCycle, float speed, float jumpHeight) : //consturct the attribute of player, animation
	animation(texture, imageCnt, switchtime, backForthCycle) //don't put semi column.
{
	this->speed = speed;
	this->originalSpeed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true; 
	body.setPosition(50.0f, 150.0f);
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
	float runSpeed = speed * 2;

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		run = true;
		speed = originalSpeed * 3;
	}
	else {
		speed = originalSpeed;
	}


	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		/*move left*/
		velocity.x = -speed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D))
	{
		/*move right*/
		velocity.x = speed;
	}
	else
	{
		velocity.x = 0;
	}
	/* jump not up and down
	if (Keyboard::isKeyPressed(Keyboard::S))
		//move down
		movement.y += speed * deltaTime;

	if (Keyboard::isKeyPressed(Keyboard::W))
		//move right
		movement.y -= speed * deltaTime;
	*/

	if (Keyboard::isKeyPressed(Keyboard::G))
	{
		//attack
		moveOrIdle = false;
		row = 2;
	}

	if (sf::Keyboard::isKeyPressed(Keyboard::W) && canJump)
	{
		canJump = false;
		velocity.y = -sqrt(2.0f * 981.0f * jumpHeight);
	}

	velocity.y += 981.0f * deltaTime;

	
	if (moveOrIdle)
	{
		if (velocity.x == 0.0f)
		{
			row = 0;
		}
		else
		{
			if (run)
				row = 3;
			else
				row = 1;
			if (velocity.x > 0.0f)
				faceRight = true;
			else
				faceRight = false;
			
		}
		
	}
	/*boundaries setting*/
	printf("%f\n", body.getPosition().x);
	if (body.getPosition().x < windowBounds.left && velocity.x < 0.0f) {
		velocity.x -= velocity.x;
	}
	if (body.getPosition().x > windowBounds.left + windowBounds.width && velocity.x > 0.0f) {
		velocity.x -= velocity.x;
	}

	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity*deltaTime);

}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		velocity.x = 0.0f;
	}

	if (direction.y > 0.0f)
	{
		velocity.y = 0.0f;
	}
	else if (direction.y < 0.0f)
	{
		velocity.y = 0.0f;
		canJump = true;
	}
}