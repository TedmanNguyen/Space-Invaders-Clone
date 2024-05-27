#include "Enemy.h"

Enemy::Enemy(int type, float spawnPositionX, float spawnPositionY)
{
	initVariables();
	initShape(type, spawnPositionX, spawnPositionY);
}

void Enemy::initVariables()
{
	enemySpeed = 1.0f;
	enemyVerticalSpeed = 1.0f;
	enemyRadius = 20;
	
	//Directional Booleans
	moveRight = true;
	moveLeft = false;
	leftBorder = false;
	rightBorder = false;
	 
}

void Enemy::initFunctions()
{
}

void Enemy::initShape(int type, 
	float spawnPositionX, float spawnPositionY)
{
	switch (type)
	{
	case 4:
		initSquare(spawnPositionX, spawnPositionY);
		break;
	case 6:
		initHexagon(spawnPositionX, spawnPositionY);
		break;
	case 8:
		initOctagon(spawnPositionX, spawnPositionY);
		break;
	}
}

void Enemy::initSquare(float spawnPositionX, float spawnPositionY)
{
	shape.setRadius(enemyRadius);
	shape.setPointCount(4);
	shape.setFillColor(sf::Color::Yellow);
	shape.setOrigin(shape.getRadius(), 0);
	shape.setPosition(spawnPositionX, spawnPositionY);
}

void Enemy::initHexagon(float spawnPositionX, float spawnPositionY)
{
	shape.setRadius(enemyRadius);
	shape.setPointCount(6);
	shape.setFillColor(sf::Color::Magenta);
	shape.setOrigin(shape.getRadius(), 0);
	shape.setPosition(spawnPositionX, spawnPositionY);
}

void Enemy::initOctagon(float spawnPositionX, float spawnPositionY)
{
	shape.setRadius(enemyRadius);
	shape.setPointCount(8);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(shape.getRadius(), 0);
	shape.setPosition(spawnPositionX, spawnPositionY);
}

void Enemy::checkBorder(sf::RenderTarget* target)
{
	//touching leftbound
	if (shape.getGlobalBounds().left <= 0.f)
	{
		leftBorder = true;
	}
	//touching right bound
	else if (shape.getGlobalBounds().left + shape.getGlobalBounds().width 
		>= target->getSize().x)
	{
		rightBorder = true;
	}
}
void Enemy::repositionDown()
{
	shape.setPosition(shape.getPosition().x, shape.getGlobalBounds().top
	+ enemyVerticalSpeed);
}

void Enemy::moveEnemyLeftRight()
{
	if (moveRight)
	{
		shape.move(enemySpeed, 0.0f);
	}
	else if (moveLeft)
	{
		shape.move(-enemySpeed, 0.0f);
	}
}

void Enemy::updateEnemy(sf::RenderTarget* target)
{
	checkBorder(target);
	moveEnemyLeftRight();
}

void Enemy::renderEnemy(sf::RenderTarget* target)
{
	target->draw(shape);
}

Enemy::~Enemy()
{
	
}
