#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Bullet.h"

class PlayerBullet : public Bullet
{
private:
//Variables
	/*
	float bulletSizeX;
	float bulletSizeY;
	int bulletSpeed;
	int resolutionHeight;
	*/


//functions


public:
//Constructors
	//PlayerBullet();
	PlayerBullet(int windowHeight, sf::Vector2f playerPosition);
	~PlayerBullet();

//Variables
	//sf::RectangleShape line; 
	//bool bulletOnBorder = false;
	

//Functions
	void initVariables(int windowHeight) override;
	void initShape(sf::Vector2f playerPosition) override;
	
	
	void moveBullet() override;
	//sf::Vector2f getBulletPosition();


	
	//void checkBulletBoundary(float resolutionHeight);
	//update

	//void update(const sf::RenderTarget& target) override;
	//render
	//void render(sf::RenderTarget& target) override;
	




};

