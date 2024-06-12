#include "Game.h"


Game::Game()
{
	initVariables();
	initWindow();
	initBackground();
	initGUI();
	initSound();
}
//Intialization Functions
void Game::initVariables()
{
	//Windows	
	videoMode.height = 1000;
	videoMode.width = 800;
	
	//Game states
	loseGame = false;
	startGame = false;
	winGame = false;
	difficultyLevel = 0;

	//Enemy Variables
	maxEnemyBullets = 1;
	squareEnemy = 4;
	hexagonEnemy = 6;
	octagonEnemy = 8;

}
void Game::initWindow()
{
	window = new sf::RenderWindow(videoMode, "Shape Invaders",
		sf::Style::Default);
	window->setFramerateLimit(60);
}
void Game::initBackground()
{
	if (!background.loadFromFile("Assets/spacePhone.jpg"))
	{
		std::cerr << "ERROR::GAME::INITBACKGROUND COULD NOT LOAD.\n";
	}
	backgroundSize = background.getSize();
	space.setTexture(background);
	space.setPosition(sf::Vector2f(0, -150));
}

void Game::initGUI()
{
	userInterface = new UserInterface(static_cast<float>(videoMode.width), 
		static_cast<float>(videoMode.height));
}

void Game::initSound()
{
	gameSound = new SoundFX();
}

const bool Game::isRunning() const
{
	return window->isOpen();
}

//Update Functions
void Game::update()
{
	pollEvents();
	updateMousePosition();

	if (startGame)
	{
		this->updateEnemy();

		if (!loseGame)
		{
			this->updatePlayer();
			this->updateGUI();
		}
	}
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
void Game::updateMousePosition()
{
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
	
	if (!startGame)
	{
		//Increase text size on mouseover
		if (userInterface->easyButton.getGlobalBounds().contains(mousePosView))
		{
			userInterface->easyModeText.setFillColor(sf::Color::Cyan);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gameSound->buttonSound.play();
				startGame = true;
				maxEnemyBullets = 1;
				spawnPlayer();
				spawnEnemy();
			}
		}
		else
		{
			userInterface->easyModeText.setFillColor(sf::Color::White);
		}
		if (userInterface->normalButton.getGlobalBounds().contains(mousePosView))
		{
			userInterface->normalModeText.setFillColor(sf::Color::Cyan);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gameSound->buttonSound.play();
				startGame = true;
				difficultyLevel = 1;
				maxEnemyBullets = 2;
				spawnPlayer();
				spawnEnemy();
			}
		}
		else
		{
			
			userInterface->normalModeText.setFillColor(sf::Color::White);
		}
		
		if (userInterface->hardButton.getGlobalBounds().contains(mousePosView))
		{
			userInterface->hardModeText.setFillColor(sf::Color::Cyan);
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gameSound->buttonSound.play();
				startGame = true;
				difficultyLevel = 2;
				maxEnemyBullets = 3;
				spawnPlayer();
				spawnEnemy();
			}
		}
		else
		{
			userInterface->hardModeText.setFillColor(sf::Color::White);
		}
	}


	//If Play Again is pressed 
	if (loseGame || winGame)
	{
		if (userInterface->tryAgainButton.getGlobalBounds().contains(mousePosView))
		{
			userInterface->tryAgainText.setFillColor(sf::Color::Cyan);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gameSound->buttonSound.play();
				startGame = false;
				loseGame = false;
				winGame = false;
				allEnemies.clear();
				allEnemyBullets.clear();
				playerPoints = 0;
				player->playerHP = 3;
				difficultyLevel = 0;
			}
		}
		else
		{
			userInterface->tryAgainText.setFillColor(sf::Color::White);
		}
	}

}
void Game::spawnPlayer()
{
	player = nullptr;
	player = new Player(static_cast<float>(videoMode.width),
		static_cast<float>(videoMode.height));
	playerPoints = 0;
}
void Game::spawnEnemy() 
{
	int enemiesPerRow = 10;
	
	//Sets the positions of enemies relative to resolution size
	float widthSpace = static_cast<float>(videoMode.width / enemiesPerRow);
	float heightSpace = static_cast<float>(videoMode.height / 9.0);

	//Spawns type of enemy at specific positions and stores in vector
	//Based on difficulty
	for (float i = 1.0; i < enemiesPerRow; i++)
	{
		if (difficultyLevel >= 2)
		{
			allEnemies.push_back(new Enemy(squareEnemy, widthSpace * i,
				heightSpace * 4.0));
		}
		if (difficultyLevel >= 1)
		{
			allEnemies.push_back(new Enemy(octagonEnemy, widthSpace * i,
				heightSpace));
			
			
		}
		if (difficultyLevel >= 0)
		{
			allEnemies.push_back(new Enemy(hexagonEnemy, widthSpace * i,
				heightSpace * 2.0));
			allEnemies.push_back(new Enemy(squareEnemy, widthSpace * i,
				heightSpace * 3.0));
		}
	}
	totalEnemies = allEnemies.size();
	currentEnemyBullets = 0;
}
void Game::updatePlayer()
{
	updatePlayerBulletCollision();
	
	if (player->playerHP <= 0)
	{
		loseGame = true;
		gameSound->playerNoLivesSound.play();
	}
	
	//Utilize player's own update
	player->update(*window);
	
}



void Game::updatePlayerBulletCollision()
{
	//create a for loop of all enemy bullets and pass into player
	int enemyBulletCounter = 0;
	for (EnemyBullet* i : allEnemyBullets)
	{
		player->checkEnemyBulletCollision(*i);
		if (player->collidedWithEnemyBullet)
		{
			player->collidedWithEnemyBullet = false;
			allEnemyBullets.erase(
				allEnemyBullets.begin() + enemyBulletCounter);
			enemyBulletCounter--;
			currentEnemyBullets--;
			gameSound->playerHitSound.play();
		}
		enemyBulletCounter++;
	}
}


void Game::updateEnemy()
{
	updateEnemySpeed();
	updateEnemyMovement();
	updateEnemyBullets();
	updateEnemyBulletBoundary();
	updateEnemyBulletCollision();
	

	if (!loseGame)
	{
		int enemyCounter = 0;
		for (Enemy* ptr : allEnemies)
		{
			//enemy touches bottom
			if (ptr->earthCollision)
			{
				allEnemies.erase(allEnemies.begin() + enemyCounter);

				enemyCounter--;

				player->playerHP--;
				gameSound->playerHitSound.play();

			}
			//enemy collides with player
			else if (ptr->playerCollision)
			{
				allEnemies.erase(allEnemies.begin() + enemyCounter);
				enemyCounter--;

				player->playerHP--;
				gameSound->playerHitSound.play();
			}
			enemyCounter++;


		}
	}

	//Check collisions with earth and with player
	

	//Run particular enemy's update method
	for (Enemy* enemyPtr : allEnemies)
	{
		enemyPtr->update(*window, *player);
	}
}
void Game::updateEnemySpeed()
{
	if (allEnemies.size() > 0)
	{
		currentEnemyPercentage =
			totalEnemies / static_cast<int>(allEnemies.size());
	}
	for (Enemy* ptr : allEnemies)
	{
		ptr->updateEnemySpeed(currentEnemyPercentage);
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
	int enemyCounter = 0;
	//Check if any Enemy has collided with player bullet
	for (Enemy* enemyPtr : allEnemies)
	{
		int bulletCounter = 0;
		for (PlayerBullet* playerBulletPtr : player->allPlayerBullets)
		{
			enemyPtr->checkBulletCollision(playerBulletPtr);
			if (enemyPtr->bulletCollision)
			{
				playerBulletPtr->enemyCollision();
				playerPoints++;
				gameSound->enemyHitSound.play();
				if (allEnemies.size() > 1)
				{
					gameSound->enemyHitSound.play();
				}
				else
				{
					gameSound->enemyHitSound.play();

					//Game win sound
					gameSound->finalEnemySound.play();
				}
			}
			//if this Player Bullet has been collided with Enemy
			//remove the bullet
			if (playerBulletPtr->collidedEnemy)
			{
				player->allPlayerBullets.erase(
					player->allPlayerBullets.begin() + bulletCounter);
				bulletCounter--;
				player->currentBullets--;
			}
			bulletCounter++;
		}
		//if enemy HAS COLLIDED, delete the enemy 
		if (enemyPtr->bulletCollision)
		{
			allEnemies.erase(allEnemies.begin() + enemyCounter);
			enemyCounter--;
		}
		enemyCounter++;
	}
	//Check amount of all enemies
	if (allEnemies.size() == 0 && !loseGame)
	{
		winGame = true;
	}
}
void Game::updateEnemyBullets()
{
	//Shoot bullets
	if (allEnemies.size() > 0 && !loseGame)
	{
		if (currentEnemyBullets < maxEnemyBullets)
		{
			//it has to be an enemy that has not been deleted

			int randomEnemyNumber = rand() % allEnemies.size();
			auto randomEnemy = allEnemies.begin() + randomEnemyNumber;
			(*randomEnemy)->shootBullets(videoMode.height,
				allEnemyBullets);
			currentEnemyBullets++;
			gameSound->enemyShootSound.play();
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
		//If Bullet touches border OR player
		if (i->bulletOnBorder || i->collidedPlayer)
		{
			//delete the bullet
			allEnemyBullets.erase(allEnemyBullets.begin() + bulletCounter);
			bulletCounter--;
			currentEnemyBullets--;
		}
		bulletCounter++;
	}

}

void Game::updateGUI()
{
	userInterface->updateGUI(winGame, loseGame, playerPoints, player->playerHP);
}

//Render Functions
void Game::render()
{
	window->clear();

	renderBackground();
	if (startGame)
	{
		this->renderPlayer();

		if (!winGame)
		{
			this->renderEnemies();
			renderEnemyBullets(*window);
		}
	}
	this->renderGUI();

	window->display();
}
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
void Game::renderPlayer()
{
	if (player->playerHP > 0)
	{
		player->render(*window);
	}


}
void Game::renderGUI()
{
	userInterface->renderGUI(startGame, loseGame, winGame, *window);
}
void Game::renderBackground()
{
	window->draw(space);
}



Game::~Game()
{
	delete player;
	player = nullptr;

	delete window;
	window = nullptr;

	delete gameSound;
	gameSound = nullptr;

	for (Enemy* ptr : allEnemies)
	{
		delete ptr;
		ptr = nullptr;
	}
	allEnemies.clear();

	for (EnemyBullet* ptr : allEnemyBullets)
	{
		delete ptr;
		ptr = nullptr;
	}
	allEnemyBullets.clear();

	delete userInterface;
	userInterface = nullptr;
}

