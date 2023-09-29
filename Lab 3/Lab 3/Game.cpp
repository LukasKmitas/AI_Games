#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ ScreenSize::s_width, ScreenSize::s_height, 32U }, "SFML Game" },
	m_exitGame{false}
{
	//setupFontAndText();
	//setupSprite();

	m_enemyStates.resize(5, true);
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
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		m_enemyStates[0] = !m_enemyStates[0];
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		m_enemyStates[1] = !m_enemyStates[1];
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		m_enemyStates[2] = !m_enemyStates[2];
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		m_enemyStates[3] = !m_enemyStates[3];
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		m_enemyStates[4] = !m_enemyStates[4];
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	m_player.update(t_deltaTime);
	sf::Vector2f playerPosition = m_player.getPosition();
	if(m_enemyStates[0])
	{
		m_enemyWander.update(t_deltaTime);
	}

	if (m_enemyStates[1])
	{
		m_enemySeek.update(t_deltaTime);
		m_enemySeek.dynamicSeek(playerPosition);
	}

	if (m_enemyStates[2])
	{
		m_enemyArriveFast.update(t_deltaTime);
		m_enemyArriveFast.dynamicArrive(playerPosition);
	}

	if (m_enemyStates[3])
	{
		m_enemyArriveSlow.update(t_deltaTime);
		m_enemyArriveSlow.dynamicArrive(playerPosition);
	}

	if (m_enemyStates[4])
	{
		m_enemyPursue.update(t_deltaTime);
	}
}

void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_welcomeMessage);
	m_window.draw(m_BackgroundSprite);

	m_player.draw(m_window);

	if (m_enemyStates[0])
	{
		m_enemyWander.draw(m_window);
	}

	if (m_enemyStates[1])
	{
		m_enemySeek.draw(m_window);
	}

	if (m_enemyStates[2])
	{
		m_enemyArriveFast.draw(m_window);
	}

	if (m_enemyStates[3])
	{
		m_enemyArriveSlow.draw(m_window);
	}

	if (m_enemyStates[4])
	{
		m_enemyPursue.draw(m_window);
	}

	m_window.display();
}

void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

void Game::setupSprite()
{
	if (!m_BackgroundTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		std::cout << "problem loading image" << std::endl;
	}
	m_BackgroundSprite.setTexture(m_BackgroundTexture);
	m_BackgroundSprite.setPosition(300.0f, 180.0f);
}
