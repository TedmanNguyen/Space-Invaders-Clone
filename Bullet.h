#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


class Bullet
{

private:

protected:
	float bulletSizeX;
	float bulletSizeY;
	int bulletSpeed;
	int resolutionHeight;
	sf::Color bulletColor;

public:
	//Constructors
	/*
	Bullet()
	{
		bulletSizeX = 5.0f;
		bulletSizeY = 45.0f;
		bulletSpeed = 0;
		resolutionHeight = 0;
	}
	*/
	Bullet(int windowHeight, sf::Vector2f agentPosition);
	virtual ~Bullet();

	//Variables
	sf::RectangleShape line;
	bool bulletOnBorder = false;
	
	//Functions
	virtual void initVariables(int windowHeight);
	virtual void initShape(sf::Vector2f agentPosition);
	virtual void moveBullet() = 0;

	void checkBulletBoundary(float resolutionHeight);
	
	
	//update
	void update(const sf::RenderTarget& target);
	
	//render
	void render(sf::RenderTarget& target);




};

