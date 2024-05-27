#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

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

	void checkBorder(sf::RenderTarget* target);
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

//Functions
	float spawnPositionX;
	float spawnPositionY;

	void repositionDown();

	void updateEnemy(sf::RenderTarget* target);
	void renderEnemy(sf::RenderTarget* target);

};

