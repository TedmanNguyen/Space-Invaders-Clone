#pragma once



#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


class Player
{
	
private:
//Variables
	float playerMovementSpeed; 
//Functions
	void initVariables();
	void initShape(float resolutionWidth,
		float resolutionHeight);


public:
//Constructors

	Player(float x,  float y);
	~Player();

//Variables
	sf::CircleShape* triangle;
	float spawnPositionX;
	float spawnPositionY;
	



//Functions

	void movePlayer();
	void update();
	void render(sf::RenderTarget* target);




};

