#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "PlayerBullet.h"
#include "EnemyBullet.h"

class Enemy
{
private:
//Variables
	float enemyRadius;
	float enemySpeed;
	float enemyVerticalSpeed;

//Functions
//Initialization
	void initVariables();
	void initShape(int type, float spawnPositionX,
		float spawnPositionY);
	void initSquare(float spawnPositionX, 
		float spawnPositionY);
	void initHexagon(float spawnPositionX,
		float spawnPositionY);
	void initOctagon(float spawnPositionX,
		float spawnPositionY);
//Update
	void checkBorder(sf::RenderTarget& target);
	void moveEnemyLeftRight();
	
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
	bool earthCollision;

//Functions
	void repositionDown();
	void updateEnemySpeed(float multiple);
	void shootBullets(float resolutionHeight,
		std::vector<EnemyBullet*>& allEnemyBullets);
	void checkBulletCollision(PlayerBullet* bullet);
	void checkEarthCollision(float resolutionHeight);

	void update(sf::RenderTarget& target);

	void render(sf::RenderTarget& target);

};

