#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


class Bullet
{
private:
//Variables
	float bulletSizeX;
	float bulletSizeY;
	int bulletSpeed;
	int resolutionHeight;


//functions
	void initVariables(int windowHeight);
	void initShape(sf::Vector2f playerPosition);

	
	void moveBullet();

	


public:
//Constructors
	Bullet();
	Bullet(int windowHeight, sf::Vector2f playerPosition);
	~Bullet();

//Variables
	sf::RectangleShape line; 
	bool bulletOnBorder = false;
	

//Functions
	//sf::Vector2f getBulletPosition();

	void checkBulletBoundary(float resolutionHeight);
	//update

	void update(const sf::RenderTarget* target);
	//render
	void render(sf::RenderTarget* target);





};

