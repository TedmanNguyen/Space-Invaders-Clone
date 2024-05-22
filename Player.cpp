#include "Player.h"

Player::Player(float resolutionWidth, float resolutionHeight)
{
	initVariables();
	initShape(resolutionWidth, resolutionHeight);		
}
void Player::initShape(float resolutionWidth, float resolutionHeight)
{
	spawnPositionX = resolutionWidth / 2;
	spawnPositionY = resolutionHeight / 1.1;
	
	triangle = new sf::CircleShape(20, 3);
	triangle->setFillColor(sf::Color::Green);
	triangle->setOrigin(triangle->getRadius(),0);
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

	//get the position of the player
	//if the player touches the edge, then move them over the screen
	//the sides in question are the width x = 0 and x = max
}



void Player::updateWindowBounds(const sf::RenderTarget* target)
{
	//Allows players to swap to other side of screen

	//Left Bound
	if (triangle->getGlobalBounds().left + triangle->getGlobalBounds().width <= 0.f)
	{
		triangle->setPosition(target->getSize().x - triangle->getGlobalBounds().width,
			triangle->getGlobalBounds().top);
	}

	//Right Bound
	if (triangle->getGlobalBounds().left >= target->getSize().x)
	{
		triangle->setPosition(0.f, triangle->getGlobalBounds().top);
	}




}
void Player::update(const sf::RenderTarget* target)
{
	movePlayer();
	updateWindowBounds(target);
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

