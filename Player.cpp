#include "Player.h"

Player::Player(float resolutionWidth, float resolutionHeight)
{
	
	
	initVariables();
	initShape(resolutionWidth, resolutionHeight);
	
		
}
void Player::initShape(float resolutionWidth, float resolutionHeight)
{
	spawnPositionX = resolutionWidth / 2;
	spawnPositionY = resolutionHeight / 2;
	
	triangle = new sf::CircleShape(80, 3);
	triangle->setFillColor(sf::Color::Green);
	triangle->setPosition(spawnPositionX, spawnPositionY);

}


void Player::initVariables()
{
	playerMovementSpeed = 5.0f;

}

void Player::movePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		triangle->move(-playerMovementSpeed, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		triangle->move(playerMovementSpeed, 0.0f);
	}
}
void Player::update()
{
	movePlayer();

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(*triangle);
	
}




Player::~Player()
{
	delete triangle;
	triangle = nullptr;
}

