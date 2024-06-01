#include "Bullet.h"
Bullet::Bullet()
{
	bulletSizeX = 5.0f;
	bulletSizeY = 45.0f;
}
Bullet::Bullet(int windowHeight, sf::Vector2f agentPosition)
{
	bulletSizeX = 5.0f;
	bulletSizeY = 45.0f;
}

void Bullet::checkBulletBoundary(float resolutionHeight) 
{
	if (line.getGlobalBounds().top <= 0.f || 
		line.getGlobalBounds().top >= resolutionHeight)
	{
		bulletOnBorder = true;
	}

}


void Bullet::update(const sf::RenderTarget& target)
{
	checkBulletBoundary(target.getSize().y);
	moveBullet();
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(line);
}


Bullet::~Bullet()
{

}

