#include "PlayerBullet.h"
/*
PlayerBullet::PlayerBullet()
{

}
*/


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
	bulletColor = sf::Color::Cyan;
	bulletSpeed = 15;
	this->resolutionHeight = windowHeight;
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

/*

//Destroys bullets when it reaches off screen
//Needs to take in resolution Height 
void PlayerBullet::checkBulletBoundary(float resolutionHeight)
{
	if (line.getGlobalBounds().top <= 0.f)
	{
		bulletOnBorder = true;
	}

}


//probably needs player position to be passed through spawn location
//to create new 


void PlayerBullet::update(const sf::RenderTarget& target)
{
	checkBulletBoundary(target.getSize().y);
	moveBullet();

}

void PlayerBullet::render(sf::RenderTarget& target)
{
	target.draw(line);

}

*/

