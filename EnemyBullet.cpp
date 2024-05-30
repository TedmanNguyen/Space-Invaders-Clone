#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(int windowHeight, sf::Vector2f enemyPosition)
	: Bullet(windowHeight, enemyPosition)
{

	initVariables(windowHeight);
	initShape(enemyPosition);

}
EnemyBullet::~EnemyBullet()
{

}
void EnemyBullet::initVariables(int windowHeight)
{
	bulletColor = sf::Color::Red;
	bulletSpeed = 5;
	this->resolutionHeight = windowHeight;
}
void EnemyBullet::initShape(sf::Vector2f enemyPosition)
{
	line.setFillColor(bulletColor);
	line.setSize(sf::Vector2<float>(bulletSizeX, bulletSizeY));
	line.setOrigin(line.getSize().x / 2, 0.f);
	line.setPosition(enemyPosition.x, enemyPosition.y);
}
void EnemyBullet::moveBullet()
{
	line.move(0.0f, bulletSpeed);
}
