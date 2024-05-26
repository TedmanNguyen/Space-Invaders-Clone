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
		if (event.type == sf::Event::Closed)
			window->close();
	}
}

void Game::updatePlayer()
{
	player->update(window);
}

void Game::updateEnemy()
{
	for (Enemy* ptr : allEnemies)
	{
		if (ptr->rightBorder)
		{
			for (Enemy* innerPtr : allEnemies)
			{
				innerPtr->moveRight = false;
				innerPtr->moveLeft = true;
				innerPtr->repositionDown();

			}
			ptr->rightBorder = false;
		}
		if (ptr->leftBorder)
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

	for (Enemy* ptr : allEnemies)
	{
		ptr->updateEnemy(window);
	}
}

void Game::update()
{
	pollEvents();
	updatePlayer();
	this->updateEnemy();
	
}

void Game::renderEnemies()
{
	for (auto i : allEnemies)
	{
		i->renderEnemy(window);
	}
}

void Game::render()
{
	window->clear();
	
	player->render(window);
	renderEnemies();

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

