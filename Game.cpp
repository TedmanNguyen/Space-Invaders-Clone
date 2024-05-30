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
	
	totalEnemies = allEnemies.size();
	maxEnemyBullets = 3;
	currentEnemyBullets = 0;
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
	updateEnemyBullets();
	updateEnemyBulletBoundary();

	//Run each enemy's own update method
	for (Enemy* ptr : allEnemies)
	{
		ptr->update(*window);
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

void Game::updateEnemyBulletCollision()
{
	
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

void Game::updateEnemyBullets()
{
	//Shoot bullets
	if (allEnemies.size() > 0)
	{
		if (currentEnemyBullets < maxEnemyBullets)
		{
			//it has to be an enemy that has not been deleted

			int randomEnemyNumber = rand() % allEnemies.size();
			auto randomEnemy = allEnemies.begin() + randomEnemyNumber;
			(*randomEnemy)->shootBullets(videoMode.height,
				allEnemyBullets);
			currentEnemyBullets++;
		}

	
	}	

	//Move bullets
	for (EnemyBullet* i : allEnemyBullets)
	{
		i->update(*window);
	}
}

void Game::updateEnemyBulletBoundary()
{
	int bulletCounter = 0;
	for (EnemyBullet* i : allEnemyBullets)
	{
		if (i->bulletOnBorder)
		{
			//fatal error
			//trying to erase something out of range. 
			
			allEnemyBullets.erase(allEnemyBullets.begin() + bulletCounter);
			bulletCounter--;
			currentEnemyBullets--;
		}
		bulletCounter++;
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
	if (allEnemies.size() > 0)
	{
		for (Enemy* i : allEnemies)
		{
			i->render(*window);
		}
	}
}
void Game::renderEnemyBullets(sf::RenderTarget& target)
{
	if (allEnemyBullets.size() > 0)
	{
		for (EnemyBullet* i : allEnemyBullets)
		{
			target.draw(i->line);
		}
	}

}
void Game::render()
{
	window->clear();
	
	player->render(*window);
	this->renderEnemies();
	renderEnemyBullets(*window);

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

