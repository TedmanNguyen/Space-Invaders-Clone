#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Bullet.h"

class PlayerBullet : public Bullet
{
private:


public:
//Constructors
	//PlayerBullet();
	PlayerBullet(int windowHeight, sf::Vector2f playerPosition);
	~PlayerBullet();

//Variables
	bool collidedEnemy;


//Functions
	void initVariables(int windowHeight) override;
	void initShape(sf::Vector2f playerPosition) override;
		
	void moveBullet() override;
	void oppositionCollision() override;




};

