#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ Global::S_WIDTH, Global::S_HEIGHT, 32U }, "Flow Field Pathfinding Algorithm" },
	m_exitGame{false},
	m_grid(),
	m_agent(m_grid)
{
	m_startTile = sf::Vector2i(-1, -1);
	m_goalTile = sf::Vector2i(-1, -1);
}

Game::~Game()
{
}

void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) 
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type)
		{
			processKeys(newEvent);
		}
		else if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			
			if (newEvent.mouseButton.button == sf::Mouse::Right)
			{
				sf::Vector2i goalTile(newEvent.mouseButton.x / Global::TILE_SIZE, newEvent.mouseButton.y / Global::TILE_SIZE);
				m_grid.setGoalTile(goalTile);
			}
			else if (newEvent.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i startTile(newEvent.mouseButton.x / Global::TILE_SIZE, newEvent.mouseButton.y / Global::TILE_SIZE);
				m_grid.setStartTile(startTile);
			}
			else if (newEvent.mouseButton.button == sf::Mouse::Middle) // Set the obstacle
			{
				sf::Vector2i obstacleTile(newEvent.mouseButton.x / Global::TILE_SIZE, newEvent.mouseButton.y / Global::TILE_SIZE);
				m_grid.setObstacleTile(obstacleTile);
			}
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Num1 == t_event.key.code) // This is to see what Number the tile is.
	{
		m_grid.toggleTextDisplay();
		std::cout << "Toggle Text Display - Button Pressed" << std::endl;
	}
	if (sf::Keyboard::Num2 == t_event.key.code) // This is to see the Tile cost.
	{
		m_grid.toggleCostDisplay();
		std::cout << "Toggle Cost Display - Button Pressed" << std::endl;
	}
	if (sf::Keyboard::Num3 == t_event.key.code) // This is to see the integrationF cost.
	{
		m_grid.toggleIntegrationFieldDisplay();
		std::cout << "Toggle Integration Display - Button Pressed" << std::endl;
	}
	if (sf::Keyboard::Num4 == t_event.key.code) // This is to see the Path from Start Tile to End (Goal) Tile.
	{
		m_grid.togglePathDisplay();
		std::cout << "Toggle Path Display - Button Pressed" << std::endl;
	}
	else if (sf::Keyboard::Num5 == t_event.key.code)
	{
		m_agent.togglePath();
		std::cout << "Toggle Path Version - Button Pressed" << std::endl;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	m_agent.update(t_deltaTime);
}

void Game::render()
{
	m_window.clear(sf::Color::Black);

	m_grid.render(m_window);

	m_agent.render(m_window);

	m_window.display();
}