#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class SoundFX
{
private:
public:
	SoundFX();
	~SoundFX();

//Variables
	//Enemy
	sf::SoundBuffer enemyHitBuffer;
	sf::Sound enemyHitSound;
	sf::SoundBuffer enemyShootBuffer;
	sf::Sound enemyShootSound;
	sf::SoundBuffer finalEnemyBuffer;
	sf::Sound finalEnemySound;
	
	//Player
	sf::SoundBuffer playerHitBuffer;
	sf::Sound playerHitSound;
	sf::SoundBuffer playerNoLivesBuffer;
	sf::Sound playerNoLivesSound;
	sf::SoundBuffer laserBuffer;
	sf::Sound laserSound;

	//Menu
	sf::SoundBuffer buttonBuffer;
	sf::Sound buttonSound;


	//Methods
	void initEnemySound();
	void initPlayerSound();
	void initMenuSound();



};

