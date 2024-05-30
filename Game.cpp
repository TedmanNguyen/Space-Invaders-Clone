#include "Game.h"


Game::Game()
{
	initVariables();
	initWindow();
	spawnPlayer();
	spawnEnemy();
}

void Game::initVariables()
{
	videoMode.height = 1000;
	videoMode.width = 600;
}

void Game::initWindow()
{
	window = new sf::RenderWindow(videoMode, "Space Invaders Clone",
		sf::Style::Default);
	window->setFramerateLimit(60);
}

void Game::spawnPlayer()
{
	player = nullptr;
	player = new Player(static_cast<float>(videoMode.width),
		static_cast<float>(videoMode.height));
}

void Game::spawnEnemy()
{
	//Sets the positions of enemies relative to resolution size
	float widthSpace = videoMode.width / 8.0;
	float heightSpace = videoMode.height / 9.0;

	//Spawns type of enemy at specific positions and stores in vector
	for (float i = 1.0; i < 8; i++)
	{
		allEnemies.push_back(new Enemy(octagonEnemy, widthSpace * i,
			heightSpace));
		
		allEnemies.push_back(new Enemy(hexagonEnemy, widthSpace * i,
			heightSpace * 2.0));

		allEnemies.push_back(new Enemy(squareEnemy, widthSpace * i,
			heightSpace * 3.0));		
	}	
}


const bool Game::isRunning() const
{
	return window->isOpen();
}

void Game::pollEvents()
{
	while (window->pollEvent(event))
	{
		
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;

		}
	}
}

//Update Functions
void Game::updatePlayer()
{
	player->update(*window);
}

void Game::updateEnemy()
{
	updateEnemyMovement();
	updateEnemyBulletCollision();

	//Run each enemy's own update method
	for (Enemy* ptr : allEnemies)
	{
		ptr->update(*window);
	}
}
void Game::updateEnemyBulletCollision()
{
	//perform a for loop with collision detection of bullets
	//for all enemies
	//run enemies's check bullet mwethod. Needs to pass through the bullet here
	//How do i pass through each bullet in the bullet class into that method?
	//I need access to the bullet vector in the player class
	for (Enemy* enemyPtr : allEnemies)
	{
		for (PlayerBullet* bulletPtr : player->allPlayerBullets)
		{
			enemyPtr->checkBulletCollision(bulletPtr);
		}
	}

	//Enemy deletion if collided w/ bullet
	int counter = 0;
	for (Enemy* ptr : allEnemies)
	{
		if (ptr->bulletCollision)
		{
			allEnemies.erase(allEnemies.begin() + counter);
			counter--;
		}
		counter++;
	}
}


void Game::updateEnemyMovement()
{
	//For all enemies, check if touching right/left border
	for (Enemy* ptr : allEnemies)
	{
		if (ptr->rightBorder)
		{
			//All must update direction
			for (Enemy* innerPtr : allEnemies)
			{
				innerPtr->moveRight = false;
				innerPtr->moveLeft = true;
				innerPtr->repositionDown();

			}
			ptr->rightBorder = false;
		}
		else if (ptr->leftBorder)
		{
			for (Enemy* innerPtr : allEnemies)
			{
				innerPtr->moveLeft = false;
				innerPtr->moveRight = true;
				innerPtr->repositionDown();
			}
			ptr->leftBorder = false;
		}
	}

}

void Game::update()
{
	pollEvents();
	updatePlayer();
	this->updateEnemy();
	
}


//Render Functions
void Game::renderEnemies()
{
	for (Enemy* i : allEnemies)
	{
		i->render(*window);
	}
}
void Game::render()
{
	window->clear();
	
	player->render(*window);
	this->renderEnemies();

	window->display();
}


Game::~Game()
{
	delete player;
	player = nullptr;

	delete window;
	window = nullptr;
	
	for (Enemy* ptr : allEnemies)
	{
		delete ptr;
	}
	allEnemies.clear();
	
}

