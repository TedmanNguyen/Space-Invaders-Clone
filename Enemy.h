#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Bullet.h"

class Enemy
{
private:
//Variables
	
	float moveDownDistance;
	int enemyRadius;
	float enemySpeed;
	float enemyVerticalSpeed;

//Functions
	void initVariables();
	void initFunctions();
	void initShape(int type, float spawnPositionX,
		float spawnPositionY);

	void initSquare(float spawnPositionX, 
		float spawnPositionY);
	void initHexagon(float spawnPositionX,
		float spawnPositionY);
	void initOctagon(float spawnPositionX,
		float spawnPositionY);

	//Movement functions
	void checkBorder(sf::RenderTarget* target);
	void moveEnemyLeftRight();

	//Bullet functions
	
	
public:
	Enemy(int type, float spawnPositionX,
		float spawnPositionY);
	~Enemy();

//Variables
	sf::CircleShape shape;
	bool leftBorder;
	bool rightBorder;
	bool moveRight;
	bool moveLeft;
	bool bulletCollision;

	//Bullet* playerBullet;

//Functions
	float spawnPositionX;
	float spawnPositionY;

	void repositionDown();

	void checkBullet(Bullet* bullet);

	void updateEnemy(sf::RenderTarget* target);
	void renderEnemy(sf::RenderTarget* target);

};

