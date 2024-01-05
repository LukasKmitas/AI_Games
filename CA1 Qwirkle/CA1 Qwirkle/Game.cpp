#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ Global::S_HEIGHT, Global::S_WIDTH, 32U }, "SFML Game" },
	m_exitGame{false}
{
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	initGameStateButtons();
	initDifficultyButtons();

	std::cout << "Default settigns are:" << std::endl;
	std::cout << "Difficulty - EASY" << std::endl;
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
		switch (currentState)
		{
		case Game::GameState::MAIN_MENU:
			if (sf::Event::MouseButtonPressed == newEvent.type)
			{
				if (sf::Mouse::Left == newEvent.mouseButton.button)
				{
					sf::Vector2f mousePos(static_cast<float>(newEvent.mouseButton.x), static_cast<float>(newEvent.mouseButton.y));
					handleGaneModeButtonClick(mousePos);
					handleDifficultyButtonClick(mousePos);
				}
			}
			break;
		case Game::GameState::GAMEPLAY:
			switch (currentPlayerTurn)
			{
			case PlayerTurn::PLAYER_1:
				processPlayer1Turn(newEvent);
				break;
			case PlayerTurn::PLAYER_2:
				processPlayer2Turn(newEvent);
				break;
			case PlayerTurn::AI:
				processAITurn();
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	switch (currentState)
	{
	case Game::GameState::MAIN_MENU:
		break;
	case Game::GameState::GAMEPLAY:
		if (sf::Keyboard::Num1 == t_event.key.code) // Toggles the bag
		{
			m_board.toggleBag();
		}
		if (sf::Keyboard::Num2 == t_event.key.code)
		{
			m_board.endTurn();
			if (currentPlayerTurn == PlayerTurn::PLAYER_1)
			{
				switch (currentGameMode)
				{
				case Game::GameMode::PLAYER_VS_PLAYER:
					currentPlayerTurn = PlayerTurn::PLAYER_2;
					break;
				case Game::GameMode::PLAYER_VS_AI:
					currentPlayerTurn = PlayerTurn::AI;
					break;
				default:
					break;
				}
				std::cout << "\nPlayers 2 Turn\n" << std::endl;
			}
			else
			{
				currentPlayerTurn = PlayerTurn::PLAYER_1;
				std::cout << "\nPlayers 1 Turn\n" << std::endl;
			}
		}
		break;
	default:
		break;
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	switch (currentState)
	{
	case Game::GameState::MAIN_MENU:
		break;
	case Game::GameState::GAMEPLAY:
		m_board.update();
		switch (currentPlayerTurn)
		{
		case Game::PlayerTurn::PLAYER_1:
			break;
		case Game::PlayerTurn::PLAYER_2:
			break;
		case Game::PlayerTurn::AI:
			processAITurn();
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Game::render()
{
	m_window.clear(sf::Color::Black);
	
	switch (currentState)
	{
	case Game::GameState::MAIN_MENU:
		m_window.draw(m_gameModeArea);
		m_window.draw(m_gameDifficultyArea);
		m_window.draw(m_gameModeAreaText);
		m_window.draw(m_gameDifficultyAreaText);

		m_window.draw(m_buttonPlayerVsPlayer);
		m_window.draw(m_textPlayerVsPlayer);
		m_window.draw(m_buttonPlayerVsAI);
		m_window.draw(m_textPlayerVsAI);

		m_window.draw(m_buttonEasy);
		m_window.draw(m_textEasy);
		m_window.draw(m_buttonMedium);
		m_window.draw(m_textMedium);
		m_window.draw(m_buttonHard);
		m_window.draw(m_textHard);
		break;
	case Game::GameState::GAMEPLAY:
		m_board.render(m_window);
		break;
	default:
		break;
	}

	m_window.display();
}

/// <summary>
/// checks for input for mouse for the player selecting tiles
/// </summary>
/// <param name="t_event"></param>
void Game::processPlayer1Turn(sf::Event t_event)
{
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		if (t_event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mousePos(static_cast<float>(t_event.mouseButton.x), static_cast<float>(t_event.mouseButton.y));
			m_board.selectedTile(mousePos, 1);
		}
	}
}

/// <summary>
/// If player vs player this checks the input for mouse
/// </summary>
/// <param name="t_event"></param>
void Game::processPlayer2Turn(sf::Event t_event)
{
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		if (t_event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2f mousePos(static_cast<float>(t_event.mouseButton.x), static_cast<float>(t_event.mouseButton.y));
			m_board.selectedTile(mousePos, 2);
		}
	}
}

/// <summary>
/// Processes the AI behaivour depending on its difficulty
/// </summary>
void Game::processAITurn()
{
	switch (currentDifficulty)
	{
	case Game::Difficulty::EASY:
		m_board.AITurn();
		break;
	case Game::Difficulty::MEDIUM:
		m_board.AIMultiplePlacements();
		break;
	case Game::Difficulty::HARD:
		m_board.MiniMax();
		break;
	default:
		break;
	}
	m_board.endTurn();
	currentPlayerTurn = PlayerTurn::PLAYER_1;
}

void Game::setGameMode(GameMode mode) 
{
	currentGameMode = mode;
}

void Game::setDifficulty(Difficulty level) 
{
	currentDifficulty = level;
}

/// <summary>
/// init Game state buttons
/// </summary>
void Game::initGameStateButtons()
{
	m_gameModeArea.setSize(sf::Vector2f(Global::S_WIDTH, Global::S_HEIGHT / 2));
	m_gameModeArea.setPosition(0, 0);
	m_gameModeArea.setFillColor(sf::Color(30, 30, 30));

	m_gameModeAreaText.setFont(m_font);
	m_gameModeAreaText.setString("Choose Game Mode");
	m_gameModeAreaText.setCharacterSize(24);
	m_gameModeAreaText.setFillColor(sf::Color::White);
	sf::FloatRect textRectGameMode = m_gameModeAreaText.getLocalBounds();
	m_gameModeAreaText.setOrigin(textRectGameMode.left + textRectGameMode.width / 2.0f,
		textRectGameMode.top + textRectGameMode.height / 2.0f);
	m_gameModeAreaText.setPosition(Global::S_WIDTH / 2, 50);

	// Set up the buttons for game mode
	m_buttonPlayerVsPlayer.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	m_buttonPlayerVsPlayer.setPosition(Global::S_WIDTH / 2 - buttonWidth - buttonSpacing / 2, Global::S_HEIGHT / 4);
	m_buttonPlayerVsPlayer.setFillColor(sf::Color::Green);

	m_textPlayerVsPlayer.setFont(m_font);
	m_textPlayerVsPlayer.setString("Player vs Player");
	m_textPlayerVsPlayer.setCharacterSize(20);
	m_textPlayerVsPlayer.setFillColor(sf::Color::Black);
	sf::FloatRect textRectPlayerVsPlayer = m_textPlayerVsPlayer.getLocalBounds();
	m_textPlayerVsPlayer.setOrigin(textRectPlayerVsPlayer.left + textRectPlayerVsPlayer.width / 2.0f,
		textRectPlayerVsPlayer.top + textRectPlayerVsPlayer.height / 2.0f);
	m_textPlayerVsPlayer.setPosition(m_buttonPlayerVsPlayer.getPosition().x + buttonWidth / 2.0f,
		m_buttonPlayerVsPlayer.getPosition().y + buttonHeight / 2.0f);

	m_buttonPlayerVsAI.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	m_buttonPlayerVsAI.setPosition(Global::S_WIDTH / 2 + buttonSpacing / 2, Global::S_HEIGHT / 4);
	m_buttonPlayerVsAI.setFillColor(sf::Color::Blue);

	m_textPlayerVsAI.setFont(m_font);
	m_textPlayerVsAI.setString("Player vs AI");
	m_textPlayerVsAI.setCharacterSize(20);
	m_textPlayerVsAI.setFillColor(sf::Color::Black);
	sf::FloatRect textRectPlayerVsAI = m_textPlayerVsAI.getLocalBounds();
	m_textPlayerVsAI.setOrigin(textRectPlayerVsAI.left + textRectPlayerVsAI.width / 2.0f,
		textRectPlayerVsAI.top + textRectPlayerVsAI.height / 2.0f);
	m_textPlayerVsAI.setPosition(m_buttonPlayerVsAI.getPosition().x + buttonWidth / 2.0f,
		m_buttonPlayerVsAI.getPosition().y + buttonHeight / 2.0f);
}

/// <summary>
/// Makes the player choose what difficulty it wants
/// Player vs player or player vs AI
/// </summary>
/// <param name="mousePos"></param>
void Game::handleGaneModeButtonClick(sf::Vector2f mousePos)
{
	if (m_buttonPlayerVsPlayer.getGlobalBounds().contains(mousePos))
	{
		std::cout << "Game mode selected - Player VS Player" << std::endl;
		setGameMode(Game::GameMode::PLAYER_VS_PLAYER);
		currentState = GameState::GAMEPLAY;
	}
	else if (m_buttonPlayerVsAI.getGlobalBounds().contains(mousePos))
	{
		std::cout << "Game mode selected - Player VS AI" << std::endl;
		setGameMode(Game::GameMode::PLAYER_VS_AI);
		currentState = GameState::GAMEPLAY;
		currentPlayerTurn = PlayerTurn::AI;
	}
}

/// <summary>
/// init difficulty buttons
/// </summary>
void Game::initDifficultyButtons()
{
	// Set up the difficulty area
	m_gameDifficultyArea.setSize(sf::Vector2f(Global::S_WIDTH, Global::S_HEIGHT / 2));
	m_gameDifficultyArea.setPosition(0, Global::S_HEIGHT / 2);
	m_gameDifficultyArea.setFillColor(sf::Color(50, 50, 50));

	m_gameDifficultyAreaText.setFont(m_font);
	m_gameDifficultyAreaText.setString("Choose Difficulty - If playing against AI");
	m_gameDifficultyAreaText.setCharacterSize(24);
	m_gameDifficultyAreaText.setFillColor(sf::Color::White);
	sf::FloatRect textRectDifficulty = m_gameDifficultyAreaText.getLocalBounds();
	m_gameDifficultyAreaText.setOrigin(textRectDifficulty.left + textRectDifficulty.width / 2.0f,
		textRectDifficulty.top + textRectDifficulty.height / 2.0f);
	m_gameDifficultyAreaText.setPosition(Global::S_WIDTH / 2, Global::S_HEIGHT / 2 + 50);

	// Set up the buttons for difficulty
	float difficultyButtonPosY = Global::S_HEIGHT / 2 + 200;

	m_buttonEasy.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	m_buttonEasy.setPosition(Global::S_WIDTH / 2 - buttonWidth - buttonSpacing / 2 - 100, difficultyButtonPosY);
	m_buttonEasy.setFillColor(sf::Color::Yellow);
	m_textEasy.setFont(m_font);
	m_textEasy.setString("Easy");
	m_textEasy.setCharacterSize(20);
	m_textEasy.setFillColor(sf::Color::Black);
	sf::FloatRect textRectEasy = m_textEasy.getLocalBounds();
	m_textEasy.setOrigin(textRectEasy.left + textRectEasy.width / 2.0f,
		textRectEasy.top + textRectEasy.height / 2.0f);
	m_textEasy.setPosition(m_buttonEasy.getPosition().x + buttonWidth / 2.0f,
		m_buttonEasy.getPosition().y + buttonHeight / 2.0f);

	m_buttonMedium.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	m_buttonMedium.setPosition(Global::S_WIDTH / 2 + buttonSpacing / 2 - 100, difficultyButtonPosY);
	m_buttonMedium.setFillColor(sf::Color::Magenta);

	m_textMedium.setFont(m_font);
	m_textMedium.setString("Medium");
	m_textMedium.setCharacterSize(20);
	m_textMedium.setFillColor(sf::Color::Black);
	sf::FloatRect textRectMedium = m_textMedium.getLocalBounds();
	m_textMedium.setOrigin(textRectMedium.left + textRectMedium.width / 2.0f,
		textRectMedium.top + textRectMedium.height / 2.0f);
	m_textMedium.setPosition(m_buttonMedium.getPosition().x + buttonWidth / 2.0f,
		m_buttonMedium.getPosition().y + buttonHeight / 2.0f);

	m_buttonHard.setSize(sf::Vector2f(buttonWidth, buttonHeight));
	m_buttonHard.setPosition(Global::S_WIDTH / 2 + buttonWidth + buttonSpacing * 1.5 - 100, difficultyButtonPosY);
	m_buttonHard.setFillColor(sf::Color::Red);

	m_textHard.setFont(m_font);
	m_textHard.setString("Hard");
	m_textHard.setCharacterSize(20);
	m_textHard.setFillColor(sf::Color::Black);
	sf::FloatRect textRectHard = m_textHard.getLocalBounds();
	m_textHard.setOrigin(textRectHard.left + textRectHard.width / 2.0f,
		textRectHard.top + textRectHard.height / 2.0f);
	m_textHard.setPosition(m_buttonHard.getPosition().x + buttonWidth / 2.0f,
		m_buttonHard.getPosition().y + buttonHeight / 2.0f);
}

/// <summary>
/// Sets difficulty
/// EASY - mean the AI can make only 1 move
/// MEDIUM - IT places all tiles that it has
/// HARD - uses MiniMax algorithm 
/// </summary>
/// <param name="mousePos"></param>
void Game::handleDifficultyButtonClick(sf::Vector2f mousePos)
{
	if (m_buttonEasy.getGlobalBounds().contains(mousePos)) 
	{
		std::cout << "Game Difficulty Set - EASY" << std::endl;
		setDifficulty(Game::Difficulty::EASY);
	}
	else if (m_buttonMedium.getGlobalBounds().contains(mousePos)) 
	{
		std::cout << "Game Difficulty Set - MEDIUM" << std::endl;
		setDifficulty(Game::Difficulty::MEDIUM);
	}
	else if (m_buttonHard.getGlobalBounds().contains(mousePos))
	{
		std::cout << "Game Difficulty Set - HARD" << std::endl;
		setDifficulty(Game::Difficulty::HARD);
	}
}

