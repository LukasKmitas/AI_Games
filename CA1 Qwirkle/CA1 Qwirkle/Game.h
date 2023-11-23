#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Board.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	Board m_board;

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window;

	bool m_exitGame; 
};

#endif

