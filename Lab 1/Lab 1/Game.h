#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Alien.h"
#include "Alien2.h"
#include "Alien3.h"

class Game
{
public:
	Game();
	~Game();
	
	void run();

private:

	Player m_player;
	Alien m_alien;
	Alien2 m_alien2;
	Alien3 m_alien3;

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window;
	sf::Font m_ArialBlackfont;
	sf::Text m_welcomeMessage;
	sf::Texture m_backgroundTexture; 
	sf::Sprite m_backgroundSprite;
	bool m_exitGame;

};

#endif

