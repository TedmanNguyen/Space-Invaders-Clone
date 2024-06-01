#include "SoundFX.h"

SoundFX::SoundFX()
{

	initEnemySound();
	initPlayerSound();
	initMenuSound();



}

SoundFX::~SoundFX()
{

}

void SoundFX::initEnemySound()
{
	if (!enemyHitBuffer.loadFromFile("Sound/enemyHit.wav"))
	{
		std::cerr << "ERROR::SoundFX::INITSOUND enemysound COULD NOT PLAY";
	}
	enemyHitSound.setBuffer(enemyHitBuffer);

	if (!finalEnemyBuffer.loadFromFile("Sound/victory.mp3"))
	{
		std::cerr << "ERROR::SoundFX::INITSOUND final enemy sound COULD NOT PLAY";
	}
	finalEnemySound.setBuffer(finalEnemyBuffer);
	finalEnemySound.setVolume(30.f);

	if (!enemyShootBuffer.loadFromFile("Sound/enemyShoot.wav"))
	{
		std::cerr << "ERROR::SoundFX::INITSOUND final enemy shoot COULD NOT PLAY";
	}
	enemyShootSound.setBuffer(enemyShootBuffer);
}

void SoundFX::initMenuSound()
{
	if (!buttonBuffer.loadFromFile("Sound/button.wav"))
	{
		std::cerr << "ERROR::SoundFX::INITSOUND button COULD NOT PLAY";
	}
	buttonSound.setBuffer(buttonBuffer);

}


void SoundFX::initPlayerSound()
{
	

	if (!playerHitBuffer.loadFromFile("Sound/playerHit.wav"))
	{
		std::cerr << "ERROR::SoundFX::INITSOUND playerHit COULD NOT PLAY";
	}
	playerHitSound.setBuffer(playerHitBuffer);
	playerHitSound.setVolume(50.f);

	if (!playerNoLivesBuffer.loadFromFile("Sound/playerNoLives.wav"))
	{
		std::cerr << "ERROR::SoundFX::INITSOUND final enemy sound COULD NOT PLAY";
	}
	playerNoLivesSound.setBuffer(playerNoLivesBuffer);
	playerNoLivesSound.setVolume(50.f);
	
	if (!laserBuffer.loadFromFile("Sound/laserShoot.wav"))
	{
		std::cerr << "ERROR::GAME::INITSOUND COULD NOT PLAY";
	}
	laserSound.setBuffer(laserBuffer);


}
