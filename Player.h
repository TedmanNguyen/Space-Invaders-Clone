#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "PlayerBullet.h"
#include "EnemyBullet.h"
#include "SoundFX.h"

#include <iostream>




class Player
{
private:
//Variables
	sf::CircleShape triangle;
	float playerMovementSpeed; 
	int maxBullets = 1;
	float spawnPositionX;
	float spawnPositionY;
	float resolutionHeight;

	SoundFX playerSound;

//Functions
//Initialization
	sf::Vector2f getPlayerPosition();
	void initVariables(float resolutionHeight);
	void initShape(float resolutionWidth,
		float resolutionHeight);

//Update
	void updateWindowBounds(const sf::RenderTarget& target);
	void movePlayer();
	void shootBullets(const sf::RenderTarget& target);
	void checkBulletBoundary();

public:
//Constructors
	Player(float x = 0,  float y = 0);
	~Player();

//Variables
	int playerHP; 
	int currentBullets = 0;
	bool collidedWithEnemyBullet;
	std::vector<PlayerBullet*> allPlayerBullets;

//Functions
	void checkEnemyBulletCollision(const EnemyBullet& enemyBullet);
	void update(const sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

