#include "PlayerBullet.h"

PlayerBullet::PlayerBullet()
{
	bulletColor = sf::Color::Yellow;
	bulletSpeed = 15.f;
	resolutionHeight = 0.f;
	collidedEnemy = false;
}

PlayerBullet::PlayerBullet(int windowHeight, sf::Vector2f playerPosition)
	: Bullet(windowHeight, playerPosition)
{
	initVariables(windowHeight);
	initShape(playerPosition);	
}
PlayerBullet::~PlayerBullet()
{

}
void PlayerBullet::initVariables(int windowHeight) 
{
	bulletColor = sf::Color::Yellow;
	bulletSpeed = 15;
	this->resolutionHeight = windowHeight;
	collidedEnemy = false;
}
void PlayerBullet::initShape(sf::Vector2f playerPosition)
{
	line.setFillColor(bulletColor);
	line.setSize(sf::Vector2<float>(bulletSizeX, bulletSizeY));
	line.setOrigin(line.getSize().x / 2, 0.f);
	line.setPosition(playerPosition.x, playerPosition.y);
}
void PlayerBullet::moveBullet()
{
	line.move(0.0f, -bulletSpeed);
}
void PlayerBullet::enemyCollision()
{
	collidedEnemy = true;
}


