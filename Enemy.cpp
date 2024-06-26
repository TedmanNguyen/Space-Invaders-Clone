#include "Enemy.h"

Enemy::Enemy(int type, float spawnPositionX, float spawnPositionY)
{
	initVariables();
	initShape(type, spawnPositionX, spawnPositionY);
}
void Enemy::initVariables()
{
	enemySpeed = 1.f;
	enemyVerticalSpeed = 6.5f;
	enemyRadius = 20.f;
	
	//Directional Booleans
	moveRight = true;
	moveLeft = false;
	leftBorder = false;
	rightBorder = false;

	//bullet collisions
	bulletCollision = false;
	earthCollision = false;
	playerCollision = false;
	 
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
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(shape.getRadius(), 0);
	shape.setPosition(spawnPositionX, spawnPositionY);
}

void Enemy::initHexagon(float spawnPositionX, float spawnPositionY)
{
	shape.setRadius(enemyRadius);
	shape.setPointCount(6);
	shape.setFillColor(sf::Color::Red);
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

void Enemy::update(sf::RenderTarget& target, Player& player)
{
	checkBorder(target);
	moveEnemyLeftRight();
	checkEarthCollision(target.getSize().y);
	checkPlayerCollision(player);
}
//Movement functions
void Enemy::checkBorder(sf::RenderTarget& target)
{
	//touching leftbound
	if (shape.getGlobalBounds().left <= 0.f)
	{
		leftBorder = true;
	}
	//touching right bound
	else if (shape.getGlobalBounds().left + shape.getGlobalBounds().width 
		>= target.getSize().x)
	{
		rightBorder = true;
	}
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
void Enemy::updateEnemySpeed(float num)
{
	//Enemy speed increases, multiplied by 
	// inverse porportion of current enemies
	enemySpeed = .8f * num;
	
}
void Enemy::repositionDown()
{
	shape.setPosition(shape.getPosition().x, shape.getGlobalBounds().top
	+ enemyVerticalSpeed);
}

//Enemy fire bullet methods
void Enemy::shootBullets(float resolutionHeight, 
	std::vector<EnemyBullet*>& allEnemyBullets)
{
	allEnemyBullets.push_back(
		new EnemyBullet(resolutionHeight, shape.getPosition()));
}

//Collisions with Player Bullet
void Enemy::checkBulletCollision(PlayerBullet* bullet)
{
	if (shape.getGlobalBounds().intersects(bullet->line.getGlobalBounds()))
	{
		bulletCollision = true;
	}
}

void Enemy::checkEarthCollision(float resolutionHeight)
{
	if (shape.getGlobalBounds().top >= resolutionHeight)
	{
		earthCollision = true;
	}

}

void Enemy::checkPlayerCollision(Player& player)
{
	if (shape.getGlobalBounds().intersects(player.triangle.getGlobalBounds()))
	{
		playerCollision = true;
	}
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(shape);
}

Enemy::~Enemy()
{
	
}
