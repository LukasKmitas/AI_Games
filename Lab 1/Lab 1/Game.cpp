#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1200U, 800U, 32U }, "SFML Game" },
	m_exitGame{false}
{
	setupFontAndText(); 
	setupSprite(); 
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
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	m_player.update(t_deltaTime);
	m_alien.update(t_deltaTime);
	//m_alien2.update(t_deltaTime);
	//m_alien3.update(t_deltaTime);

	sf::Vector2f playerPosition = m_player.getPosition();

	//m_alien2.kinematicSeek(playerPosition);
	m_alien2.kinematicArrive(playerPosition);

	m_alien3.kinematicFlee(playerPosition);
}

void Game::render()
{
	m_window.clear(sf::Color::White);

	//m_window.draw(m_welcomeMessage);
	m_window.draw(m_backgroundSprite);

	m_player.draw(m_window);
	m_alien.draw(m_window);
	m_alien2.draw(m_window);
	m_alien3.draw(m_window);

	m_window.display();
}

void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("Assets\\Fonts\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
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
	if (!m_backgroundTexture.loadFromFile("Assets\\Images\\space-background.png"))
	{
		std::cout << "problem loading logo" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(0.0f, 0.0f);
	m_backgroundSprite.setScale(
		m_window.getSize().x / m_backgroundSprite.getLocalBounds().width,
		m_window.getSize().y / m_backgroundSprite.getLocalBounds().height
	);
}
