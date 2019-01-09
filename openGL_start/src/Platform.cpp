//pf.cpp

#include "Platform.h"
#include "SFML/Graphics.hpp"
#include "Collider.h"



Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);
	body.setPosition(position);
	body.setTexture(texture);
	body.setOrigin(size / 2.0f);
}


Platform::~Platform()
{
}

void Platform::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Platform::SetHorizontalPosition(float x)
{
	this->body.setPosition(x, this->getPosition().y);
}

void Platform::SetVerticalPosition(float y)
{
	this->body.setPosition(this->getPosition().x, y);
}
