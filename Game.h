#pragma once
#include <iostream>
#include <ctime>
#include <vector>

#include "Player.h"
#include "Enemy.h"


class Game
{
private:	
	sf::Event event;
	const int squareEnemy = 4;
	const int hexagonEnemy = 6;
	const int octagonEnemy = 8;

//Variables
	Player* player;
	Enemy* enemy;
	std::vector<Enemy*> allEnemies;
	int maxEnemies;
	int totalEnemies;


//Functions
	void initVariables();
	void initWindow();
	void spawnPlayer();
	void spawnEnemy();
	void pollEvents();

public:
	Game();
	~Game();

//Getter
	const bool isRunning() const;

//Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;

	PlayerBullet* bullet;

//Functions
	void updatePlayer();
	void updateEnemy();
	void updateEnemyMovement();
	void updateEnemyBulletCollision();

	void update();

	void renderEnemies();
	void render();
};

