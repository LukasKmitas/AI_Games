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

	enum class GameState {MAIN_MENU, GAMEPLAY};
	enum class PlayerTurn { PLAYER_1, PLAYER_2, AI };
	enum class GameMode { PLAYER_VS_PLAYER, PLAYER_VS_AI };
	enum class Difficulty { EASY, MEDIUM, HARD };

	GameState currentState = GameState::MAIN_MENU;
	PlayerTurn currentPlayerTurn = PlayerTurn::PLAYER_1;
	GameMode currentGameMode = GameMode::PLAYER_VS_PLAYER;
	Difficulty currentDifficulty = Difficulty::EASY;

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void processPlayer1Turn(sf::Event t_event);
	void processPlayer2Turn(sf::Event t_event);
	void processAITurn();

	void setGameMode(GameMode mode);
	void setDifficulty(Difficulty level);

	void initGameStateButtons();
	void handleGaneModeButtonClick(sf::Vector2f mousePos);
	void initDifficultyButtons();
	void handleDifficultyButtonClick(sf::Vector2f mousePos);

	float buttonWidth = 200;
	float buttonHeight = 50;
	float buttonSpacing = 20;

	sf::RectangleShape m_gameModeArea;
	sf::RectangleShape m_gameDifficultyArea;

	sf::RectangleShape m_buttonPlayerVsPlayer;
	sf::RectangleShape m_buttonPlayerVsAI;
	sf::RectangleShape m_buttonEasy;
	sf::RectangleShape m_buttonMedium;
	sf::RectangleShape m_buttonHard;

	sf::Font m_font;
	sf::Text m_gameModeAreaText;
	sf::Text m_gameDifficultyAreaText;
	sf::Text m_textPlayerVsPlayer;
	sf::Text m_textPlayerVsAI;
	sf::Text m_textEasy;
	sf::Text m_textMedium;
	sf::Text m_textHard;

	sf::RenderWindow m_window;

	bool m_exitGame; 
};

#endif

