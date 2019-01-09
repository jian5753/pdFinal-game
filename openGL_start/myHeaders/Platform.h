//	pf.h

#pragma once
#include <SFML/Graphics.hpp>
#include <Collider.h>
class Platform
{
public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Platform();

	void Draw(sf::RenderWindow& window);
	sf::Vector2f getPosition() { return body.getPosition(); }
	void setVerticalVelocity(float f)
	{
		body.move(sf::Vector2f(0.0f, f));
	}

	void SetHorizontalPosition(float x);
	void SetVerticalPosition(float y);

	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
};