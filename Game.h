#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

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
	bool gameOver;


	Player* player;
	int playerPoints;

	Enemy* enemy;
	std::vector<Enemy*> allEnemies;
	int totalEnemies;
	float currentEnemyPercentage;
	std::vector<EnemyBullet*> allEnemyBullets;
	int maxEnemyBullets;
	int currentEnemyBullets;


//Functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initGUI();


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

	sf::Font fonts;
	sf::Text inGameText;
	sf::Text preGameText;
	sf::Text endGameText;
	

//Functions

	void updatePlayer();
	void updatePlayerBulletCollision();

	void updateEnemy();
	void updateEnemySpeed();
	void updateEnemyMovement();
	void updateEnemyBulletCollision();
	void updateEnemyBullets();
	void updateEnemyBulletBoundary();

	void updateGUI();

	void update();

	void renderEnemies();
	void renderEnemyBullets(sf::RenderTarget& target);

	void renderGUI();
	void render();
};

