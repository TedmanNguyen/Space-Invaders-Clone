#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


class Bullet
{
private:

protected:
	float bulletSizeX;
	float bulletSizeY;

public:
	//Constructors	
	Bullet();
	Bullet(int windowHeight, sf::Vector2f agentPosition);
	virtual ~Bullet();

	//Variables
	sf::RectangleShape line;
	bool bulletOnBorder = false;
	
	//Functions
	void checkBulletBoundary(float resolutionHeight);

	//Functions to override
	virtual void initVariables(int windowHeight) = 0;
	virtual void initShape(sf::Vector2f agentPosition) = 0;
	virtual void moveBullet() = 0;

	//update
	void update(const sf::RenderTarget& target);
	
	//render
	void render(sf::RenderTarget& target);




};

