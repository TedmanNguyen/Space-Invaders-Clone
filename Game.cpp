#include "Game.h"


Game::Game()
{
	initVariables();
	initWindow();
	initPlayer();
}


void Game::initVariables()
{
	videoMode.height = 600;
	videoMode.width = 800;
	
}

void Game::initWindow()
{
	window = new sf::RenderWindow(videoMode, "Space Invaders Clone",
		sf::Style::Default);
	window->setFramerateLimit(60);
}

void Game::initPlayer()
{
	player = nullptr;
	player = new Player(static_cast<float>(videoMode.width),
		static_cast<float>(videoMode.height));
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

void Game::update()
{
	pollEvents();
	updatePlayer();
	
}

void Game::render()
{
	window->clear();
	
	player->render(window);

	window->display();
}


Game::~Game()
{
	delete player;
	player = nullptr;


	delete window;
	window = nullptr;

	
}

