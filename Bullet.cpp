#include "Bullet.h"

Bullet::Bullet(int windowHeight, sf::Vector2f agentPosition)
{
	bulletSizeX = 5.0f;
	bulletSizeY = 45.0f;
	
	
}

Bullet::~Bullet()
{

}

void Bullet::checkBulletBoundary(float resolutionHeight) 
{
	if (line.getGlobalBounds().top <= 0.f || 
		line.getGlobalBounds().top >= resolutionHeight)
	{
		bulletOnBorder = true;
	}

}

void Bullet::initVariables(int windowHeight)
{
	bulletColor = sf::Color::White;
	bulletSpeed = 1;
	this->resolutionHeight = windowHeight;
}


void Bullet::initShape(sf::Vector2f agentPosition)
{
	line.setFillColor(bulletColor);
	line.setSize(sf::Vector2<float>(bulletSizeX, bulletSizeY));
	line.setOrigin(line.getSize().x / 2, 0.f);
	line.setPosition(agentPosition.x, agentPosition.y);
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


