#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <sstream>

class UserInterface
{
private:


public:
	UserInterface();
	UserInterface(float resolutionWidth, float resolutionHeight);
	~UserInterface();

	sf::Font fonts;
	sf::Text titleText;

	sf::Text inGameText;
	sf::Text endGameText;
	sf::Text tryAgainText;

	sf::Text winGameText;

	sf::Text easyModeText;
	sf::Text normalModeText;
	sf::Text hardModeText;

	sf::RectangleShape easyButton;
	sf::RectangleShape normalButton;
	sf::RectangleShape hardButton;
	sf::RectangleShape tryAgainButton;

	float resolutionWidth;



	void initFont();
	void initText(float resolutionWidth, float resolutionHeight);
	void initButtons(float resolutionWidth, float resolutionHeight);

	void updateGUI(bool winGame, bool gameOver, int playerPoints, int playerHP);
	
	void renderGUI(const bool& startGame, const bool& gameOver,
		const bool& winGame, sf::RenderTarget& target);


};

