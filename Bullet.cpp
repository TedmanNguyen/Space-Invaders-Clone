#include "Bullet.h"

Bullet::Bullet(int windowHeight, sf::Vector2f playerPosition)
{
	initVariables(windowHeight);
	initShape(playerPosition);
}

Bullet::~Bullet()
{


}

void Bullet::initVariables(int windowHeight)
{
	bulletSpeed = 15;
	this->resolutionHeight = windowHeight;
	bulletSizeX = 5.0f;
	bulletSizeY = 45.0f;
}

void Bullet::initShape(sf::Vector2f playerPosition)
{
	line.setFillColor(sf::Color::Cyan);
	line.setSize(sf::Vector2<float>(bulletSizeX, bulletSizeY));
	line.setOrigin(line.getSize().x / 2, 0.f);
	line.setPosition(playerPosition.x, playerPosition.y);
}

void Bullet::moveBullet()
{
	line.move(0.0f, -bulletSpeed);
}



//Destroys bullets when it reaches off screen
//Needs to take in resolution Height 
void Bullet::checkBulletBoundary(float resolutionHeight)
{
	if (line.getGlobalBounds().top <= 0.f)
	{
		bulletOnBorder = true;
	}

}

//probably needs player position to be passed through spawn location
//to create new 


void Bullet::update(const sf::RenderTarget* target)
{
	checkBulletBoundary(target->getSize().y);
	moveBullet();

}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(line);

}