#pragma once


#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include "Player.h"
#include "Enemy.h"
#include "UserInterface.h"
#include "SoundFX.h"


class Game
{
private:	
//Variables
	//Window
	sf::Event event;

	//Game States
	bool loseGame;
	bool startGame;
	bool winGame;
	int difficultyLevel;

	//Background
	sf::Texture background;
	sf::Sprite space;
	sf::Vector2u backgroundSize;

	//Sound
	SoundFX* gameSound;

	//UI
	UserInterface* userInterface;

	//Mouse
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Player
	Player* player;
	int playerPoints;

	//Enemy
	Enemy* enemy;
	std::vector<Enemy*> allEnemies;
	int totalEnemies;
	int squareEnemy;
	int hexagonEnemy;
	int octagonEnemy;
	float currentEnemyPercentage;

	//Enemy Bullets
	std::vector<EnemyBullet*> allEnemyBullets;
	int maxEnemyBullets;
	int currentEnemyBullets;


//Functions
//Initialization
	void initVariables();
	void initWindow();
	void initBackground();
	void initGUI();
	void initSound();

	void spawnPlayer();
	void spawnEnemy();
	void pollEvents();

//Update
	//GUI
	void updateMousePosition();
	void updateGUI();

	//Player
	void updatePlayer();
	void updatePlayerBulletCollision();
	
	//Enemy
	void updateEnemy();
	void updateEnemySpeed();
	void updateEnemyMovement();
	void updateEnemyBulletCollision();
	void updateEnemyBullets();
	void updateEnemyBulletBoundary();


	
//Render
	//Enemies
	void renderEnemies();
	void renderEnemyBullets(sf::RenderTarget& target);

	//Player
	void renderPlayer();

	//GUI
	void renderGUI();
	void renderBackground();
	
public:
	Game();
	~Game();

//Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	
//Functions
	const bool isRunning() const;
	void update();	
	void render();
	

	
};

