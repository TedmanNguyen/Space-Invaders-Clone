#include "Player.h"

Player::Player(float resolutionWidth, float resolutionHeight)
{
	this->resolutionHeight = resolutionHeight;
	initVariables(resolutionHeight);
	initShape(resolutionWidth, resolutionHeight);		
}
void Player::initShape(float resolutionWidth, float resolutionHeight)
{
	spawnPositionX = resolutionWidth / 2;
	spawnPositionY = resolutionHeight / 1.1;
	
	//triangle = new sf::CircleShape(20, 3);
	triangle.setRadius(20);
	triangle.setPointCount(3);
	triangle.setFillColor(sf::Color::Green);
	triangle.setOrigin(triangle.getRadius(),0);
	triangle.setPosition(spawnPositionX, spawnPositionY);
}


sf::Vector2f Player::getPlayerPosition()
{
	return triangle.getPosition();
}

void Player::initVariables(float resolutionHeight)
{
	this->resolutionHeight = resolutionHeight;
	playerMovementSpeed = 7.0f;

}

void Player::movePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		triangle.move(-playerMovementSpeed, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		triangle.move(playerMovementSpeed, 0.0f);
	}
}

void Player::shootBullets(const sf::RenderTarget& target)
{
	if (currentBullets < maxBullets)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//create bullets at current position

			//add to vector
			allPlayerBullets.push_back(new PlayerBullet(resolutionHeight, 
				triangle.getPosition()));
			currentBullets++;
		}
	}
	
	if (!allPlayerBullets.empty())
	{
		for (PlayerBullet* i : allPlayerBullets)
		{
			i->update(target);
		}
	}
}

void Player::checkBulletBoundary()
{
	int bulletCounter = 0;
	for (PlayerBullet* i : allPlayerBullets)
	{
		if (i->bulletOnBorder)
		{
			allPlayerBullets.erase(allPlayerBullets.begin() + bulletCounter);
			currentBullets--;
		}
		bulletCounter++;
	}
}

void Player::updateWindowBounds(const sf::RenderTarget& target)
{
	//Allows players to swap to other side of screen

	//Left Bound
	if (triangle.getGlobalBounds().left + triangle.getGlobalBounds().width <= 0.f)
	{
		triangle.setPosition(target.getSize().x, triangle.getGlobalBounds().top);
	}

	//Right Bound
	if (triangle.getGlobalBounds().left >= target.getSize().x)
	{
		triangle.setPosition(0.f, triangle.getGlobalBounds().top);
	}

}

void Player::update(const sf::RenderTarget& target)
{
	movePlayer();
	shootBullets(target);
	checkBulletBoundary();
	updateWindowBounds(target);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(triangle);
	for (PlayerBullet* i : allPlayerBullets)
	{
		i->render(target);
	}
}

Player::~Player()
{
	for (PlayerBullet* ptr : allPlayerBullets)
	{
		delete ptr;
	}
	
	allPlayerBullets.clear();
}

