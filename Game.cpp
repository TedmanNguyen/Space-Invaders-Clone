#include "Game.h"


Game::Game()
{
	initVariables();
	initWindow();
	initFonts();
	initGUI();
	spawnPlayer();
	spawnEnemy();
}

void Game::initVariables()
{
	videoMode.height = 1000;
	videoMode.width = 500;
	gameOver = false;
}

void Game::initWindow()
{
	window = new sf::RenderWindow(videoMode, "Space Invaders Clone",
		sf::Style::Default);
	window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!fonts.loadFromFile("Fonts/space_invaders.ttf"))
	{
		std::cerr << "ERROR::GAME::INITFONTS::COULD NOT LOAD space_invaders.ttf"
			<< "\n";
	}

}

void Game::initGUI()
{
	inGameText.setFont(fonts);
	inGameText.setFillColor(sf::Color::White);
	inGameText.setCharacterSize(30);
	inGameText.setPosition(sf::Vector2f(20, 50));

	//inGameText.setString("Health")


	endGameText.setFont(fonts);
	endGameText.setFillColor(sf::Color::White);
	endGameText.setCharacterSize(70);
	endGameText.setPosition(sf::Vector2f(20, 300));
	endGameText.setString("GAME OVER!");


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
	updatePlayerBulletCollision();
	if (player->playerHP == 0)
	{
		gameOver = true;
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
		}
		enemyBulletCounter++;
	}




}

void Game::updateEnemy()
{
	updateEnemyMovement();
	updateEnemySpeed();
	updateEnemyBulletCollision();
	updateEnemyBullets();
	updateEnemyBulletBoundary();

	

	//Run each enemy's own update method
	for (Enemy* ptr : allEnemies)
	{
		ptr->updateEnemySpeed(currentEnemyPercentage);
		ptr->update(*window);
	}
}

void Game::updateEnemySpeed()
{
	if (allEnemies.size() > 0)
	{
		currentEnemyPercentage =
			totalEnemies / static_cast<int>(allEnemies.size());
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
		for (PlayerBullet* bulletPtr : player->allPlayerBullets)
		{
			enemyPtr->checkBulletCollision(bulletPtr);
			if (enemyPtr->bulletCollision)
			{
				bulletPtr->oppositionCollision();
				playerPoints++;
			}
			
			//if this bullet has been collided with, 
			//remove the bullet
			if (bulletPtr->collidedEnemy)
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
		//If Bullet touches border OR player
		if (i->bulletOnBorder || i->collidedPlayer)
		{
			//fatal error trying to erase something out of range. 
			//fixed by making sure to decrement bulletCounter
			allEnemyBullets.erase(allEnemyBullets.begin() + bulletCounter);
			bulletCounter--;
			currentEnemyBullets--;
		}
		bulletCounter++;
	}

}

void Game::updateGUI()
{
	std::stringstream stringstream;
	stringstream << "POINTS: " << playerPoints
		<< "           "
		<< "HEALTH: " << player->playerHP;
	inGameText.setString(stringstream.str());



}


void Game::update()
{
	pollEvents();

	this->updateEnemy();

	if (!gameOver)
	{
		updatePlayer();
		updateGUI();
	}
		
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
void Game::renderGUI()
{
	window->draw(inGameText);
	if (gameOver)
	{
		window->draw(endGameText);
	}
}
void Game::render()
{
	window->clear();

	
	if (player->playerHP > 0)
	{
		player->render(*window);
	}
	this->renderEnemies();
	renderEnemyBullets(*window);
	renderGUI();
	
	

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
		ptr = nullptr;
	}
	allEnemies.clear();

	for (EnemyBullet* ptr : allEnemyBullets)
	{
		delete ptr;
		ptr = nullptr;
	}
	allEnemyBullets.clear();
	
}

