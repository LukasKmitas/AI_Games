#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"

#include "Player.h"

#include "Enemy.h"

class Game
{
public:
	Game();
	~Game();
	
	void run();

private:

	Player m_player;
	Enemy m_enemy;

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

	bool m_exitGame;

};

#endif 

