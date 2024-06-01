#include "UserInterface.h"

UserInterface::UserInterface() 
{
	resolutionWidth = 0;
}

UserInterface::UserInterface(float resolutionWidth, float resolutionHeight)
{
	this->resolutionWidth = resolutionWidth;
	initFont();
	initText(resolutionWidth, resolutionHeight);
	initButtons(resolutionWidth, resolutionHeight);


}

UserInterface::~UserInterface()
{


}


void UserInterface::initFont()
{
	if (!fonts.loadFromFile("Fonts/space_invaders.ttf"))
	{
		std::cerr << "ERROR::GAME::INITFONTS::COULD NOT LOAD space_invaders.ttf"
			<< "\n";
	}
}

void UserInterface::initText(float resolutionWidth, float resolutionHeight)
{
	std::stringstream titleStream;
	titleStream << "    SHAPE\n"
		<< "INVADERS";

	titleText.setFont(fonts);
	titleText.setFillColor(sf::Color::White);
	titleText.setCharacterSize(70);
	titleText.setPosition(sf::Vector2f(50, 300));
	titleText.setString(titleStream.str());

	easyModeText.setFont(fonts);
	easyModeText.setOrigin(70.f, 0.f);
	easyModeText.setFillColor(sf::Color::White);
	easyModeText.setCharacterSize(50);
	easyModeText.setPosition(sf::Vector2f(resolutionWidth / 2, 620));
	easyModeText.setString("EASY");

	normalModeText.setFont(fonts);
	normalModeText.setOrigin(70.f, 0.f);
	normalModeText.setFillColor(sf::Color::White);
	normalModeText.setCharacterSize(50);
	normalModeText.setPosition(sf::Vector2f(resolutionWidth / 2.3, 720));
	normalModeText.setString("NORMAL");

	hardModeText.setFont(fonts);
	hardModeText.setOrigin(70.f, 0.f);
	hardModeText.setFillColor(sf::Color::White);
	hardModeText.setCharacterSize(50);
	hardModeText.setPosition(sf::Vector2f(resolutionWidth / 2, 820));
	hardModeText.setString("HARD");

	inGameText.setFont(fonts);
	inGameText.setFillColor(sf::Color::White);
	inGameText.setCharacterSize(30);
	inGameText.setPosition(sf::Vector2f(20, 50));

	endGameText.setFont(fonts);
	endGameText.setFillColor(sf::Color::White);
	endGameText.setCharacterSize(70);
	endGameText.setPosition(sf::Vector2f(20, 300));
	endGameText.setString("GAME OVER!");

	tryAgainText.setFont(fonts);
	tryAgainText.setFillColor(sf::Color::White);
	tryAgainText.setCharacterSize(60);
	tryAgainText.setPosition(sf::Vector2f(140, 520));
	tryAgainText.setString("AGAIN!");

	winGameText.setFont(fonts);
	winGameText.setFillColor(sf::Color::White);
	winGameText.setCharacterSize(70);
	winGameText.setPosition(sf::Vector2f(80, 300));
	winGameText.setString("YOU WIN!");

}

void UserInterface::initButtons(float resolutionWidth, float resolutionHeight)
{
	sf::Vector2f easyButtonSize(300.f, 100.f);
	easyButton.setSize(easyButtonSize);
	easyButton.setOrigin(easyButtonSize.x / 2, 0);
	easyButton.setPosition(sf::Vector2f(resolutionWidth / 2, 600.f));
	easyButton.setFillColor(sf::Color::Black);
	easyButton.setOutlineColor(sf::Color::White);
	easyButton.setOutlineThickness(5.f);

	sf::Vector2f normalButtonSize(300.f, 100.f);
	normalButton.setSize(normalButtonSize);
	normalButton.setOrigin(normalButtonSize.x / 2, 0);
	normalButton.setPosition(sf::Vector2f(resolutionWidth / 2, 700.f));
	normalButton.setFillColor(sf::Color::Black);
	normalButton.setOutlineColor(sf::Color::White);
	normalButton.setOutlineThickness(5.f);

	sf::Vector2f hardButtonSize(300.f, 100.f);
	hardButton.setSize(hardButtonSize);
	hardButton.setOrigin(hardButtonSize.x / 2, 0);
	hardButton.setPosition(sf::Vector2f(resolutionWidth / 2, 800.f));
	hardButton.setFillColor(sf::Color::Black);
	hardButton.setOutlineColor(sf::Color::White);
	hardButton.setOutlineThickness(5.f);
}

void UserInterface::updateGUI(bool winGame, bool loseGame, int playerPoints, int playerHP)
{
	std::stringstream stringstream;
	stringstream << "POINTS: " << playerPoints
		<< "           "
		<< "HEALTH: " << playerHP;
	inGameText.setString(stringstream.str());

	if (winGame || loseGame)
	{
		sf::Vector2f tryAgainButtonSize(300.f, 100.f);
		tryAgainButton.setSize(tryAgainButtonSize);
		tryAgainButton.setOrigin(tryAgainButtonSize.x / 2, 0);
		tryAgainButton.setPosition(sf::Vector2f(resolutionWidth / 2, 500.f));
		tryAgainButton.setFillColor(sf::Color::Black);
		tryAgainButton.setOutlineColor(sf::Color::White);
		tryAgainButton.setOutlineThickness(5.f);
	}


}

void UserInterface::renderGUI(const bool& startGame, const bool& loseGame, 
	const bool& winGame, sf::RenderTarget& target)
{
	if (startGame)
	{
		target.draw(inGameText);

		if (loseGame && !winGame)
		{
			target.draw(endGameText);
			target.draw(tryAgainButton);
			target.draw(tryAgainText);
			
		}
		else if (winGame)
		{
			target.draw(winGameText);
			target.draw(tryAgainButton);
			target.draw(tryAgainText);
		}
	}
	else
	{
		target.draw(titleText);
		target.draw(easyButton);
		target.draw(easyModeText);
		target.draw(normalButton);
		target.draw(normalModeText);
		target.draw(hardButton);
		target.draw(hardModeText);
	}
}
