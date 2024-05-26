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
	void updateWindowBounds(const sf::RenderTarget* target);
	void movePlayer();

public:
//Constructors

	Player(float x = 0,  float y = 0);
	~Player();

//Variables
	sf::CircleShape triangle;
	float spawnPositionX;
	float spawnPositionY;


//Functions
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

