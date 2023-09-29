#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"

#include "Player.h"

#include "EnemyWander.h"
#include "EnemySeek.h"
#include "EnemyArriveFast.h"
#include "EnemyArriveSlow.h"
#include "EnemyPursue.h"

class Game
{
public:
	Game();
	~Game();
	
	void run();

private:

	std::vector<bool> m_enemyStates;

	Player m_player;
	EnemyWander m_enemyWander;
	EnemySeek m_enemySeek;
	EnemyArriveFast m_enemyArriveFast;
	EnemyArriveSlow m_enemyArriveSlow;
	EnemyPursue m_enemyPursue;

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; 

	sf::Font m_ArialBlackfont; 
	sf::Text m_welcomeMessage;

	sf::Texture m_BackgroundTexture; 
	sf::Sprite m_BackgroundSprite;

	float predictTime = 1.0f;
	float maxTimePrediction = 2.0f;

	bool m_exitGame;

};

#endif 

