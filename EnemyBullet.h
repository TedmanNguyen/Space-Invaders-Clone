#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Bullet.h"
class EnemyBullet : public Bullet
{
private:


public:
	//Constructors
		//PlayerBullet();
	EnemyBullet(int windowHeight, sf::Vector2f playerPosition);
	~EnemyBullet();

	//Functions
	void initVariables(int windowHeight) override;
	void initShape(sf::Vector2f playerPosition) override;

	void moveBullet() override;




};

