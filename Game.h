#pragma once
#include <iostream>
#include <ctime>


#include "Player.h"

class Player;

class Game
{
	

private:
	
	sf::Event event;
	

//Variables
	Player* player;

//Functions
	void initVariables();
	void initWindow();
	void initPlayer();
	void pollEvents();

public:
	Game();
	~Game();

//Getter
	const bool isRunning() const;


//Variables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;



//Functions
	void update();
	void render();







	




};

