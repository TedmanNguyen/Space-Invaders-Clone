#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Bullet.h"
class EnemyBullet : public Bullet
{
private:
	sf::Color bulletColor;
	float bulletSpeed;
	float resolutionHeight;

public:
	//Constructors
	EnemyBullet();
	EnemyBullet(int windowHeight, sf::Vector2f playerPosition);
	~EnemyBullet();

	//Variables
	bool collidedPlayer; 

	//Functions
	void initVariables(int windowHeight) override;
	void initShape(sf::Vector2f playerPosition) override;
	void moveBullet() override;

};

