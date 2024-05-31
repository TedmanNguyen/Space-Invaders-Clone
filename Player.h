#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "PlayerBullet.h"
#include "EnemyBullet.h"


class Player
{
private:
//Variables
	sf::Event event;
	float playerMovementSpeed; 
	sf::Vector2f getPlayerPosition();
	
	int maxBullets = 1;
	
//Functions
	void initVariables(float resolutionHeight);
	void initShape(float resolutionWidth,
		float resolutionHeight);

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
	bool collidedWithEnemyBullet;

	int currentBullets = 0;
	sf::CircleShape triangle;
	float spawnPositionX;
	float spawnPositionY;
	float resolutionHeight;

	std::vector<PlayerBullet*> allPlayerBullets;

//Functions
	void checkEnemyBulletCollision(const EnemyBullet& enemyBullet);


	void update(const sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

