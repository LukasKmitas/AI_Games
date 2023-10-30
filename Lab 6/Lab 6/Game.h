#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Grid.h"
#include "Agent.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	Grid m_grid;
	Agent m_agent;

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window;
	
	sf::Vector2i m_startTile;
	sf::Vector2i m_goalTile;

	bool m_displayCostField;
	bool m_displayFlowField;

	bool m_exitGame;
};
#endif