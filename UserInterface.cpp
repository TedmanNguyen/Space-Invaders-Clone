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
	titleText.setString(titleStream.str());
	titleText.setCharacterSize(120);
	titleText.setOrigin(titleText.getGlobalBounds().width / 2, 0.f);
	titleText.setPosition(sf::Vector2f(resolutionWidth / 2, resolutionHeight / 5));
	

	easyModeText.setFont(fonts);
	easyModeText.setString("EASY");
	easyModeText.setFillColor(sf::Color::White);
	easyModeText.setCharacterSize(50);
	easyModeText.setOrigin(easyModeText.getGlobalBounds().width / 2, 0.f);
	easyModeText.setPosition(sf::Vector2f(resolutionWidth / 2, 620));
	

	normalModeText.setFont(fonts);
	normalModeText.setFillColor(sf::Color::White);
	normalModeText.setString("NORMAL");
	normalModeText.setCharacterSize(50);
	normalModeText.setOrigin(normalModeText.getGlobalBounds().width / 2, 0.f);
	normalModeText.setPosition(sf::Vector2f(resolutionWidth / 2, 720));
	

	hardModeText.setFont(fonts);
	hardModeText.setString("HARD");
	hardModeText.setFillColor(sf::Color::White);
	hardModeText.setCharacterSize(50);
	hardModeText.setOrigin(hardModeText.getGlobalBounds().width / 2, 0.f);
	hardModeText.setPosition(sf::Vector2f(resolutionWidth / 2, 820));
	

	inGameText.setFont(fonts);
	inGameText.setFillColor(sf::Color::White);
	inGameText.setCharacterSize(30);
	inGameText.setPosition(sf::Vector2f(20, 50));

	endGameText.setFont(fonts);
	endGameText.setString("GAME OVER!");
	endGameText.setFillColor(sf::Color::White);
	endGameText.setCharacterSize(100);
	endGameText.setOrigin(endGameText.getGlobalBounds().width / 2, 0);
	endGameText.setPosition(sf::Vector2f(resolutionWidth / 2, 300));
	

	tryAgainText.setFont(fonts);
	tryAgainText.setString("AGAIN!");
	tryAgainText.setFillColor(sf::Color::White);
	tryAgainText.setCharacterSize(60);
	tryAgainText.setPosition(sf::Vector2f(resolutionWidth / 2, 520));
	tryAgainText.setOrigin(tryAgainText.getGlobalBounds().width / 2, 0.f);
	tryAgainText.setString("AGAIN!");

	winGameText.setFont(fonts);
	winGameText.setString("YOU WIN!");
	winGameText.setFillColor(sf::Color::White);
	winGameText.setCharacterSize(120);
	winGameText.setOrigin(winGameText.getGlobalBounds().width / 2, 0.f);
	winGameText.setPosition(sf::Vector2f(resolutionWidth / 2, 300));
	

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
		<< "                                                "
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
