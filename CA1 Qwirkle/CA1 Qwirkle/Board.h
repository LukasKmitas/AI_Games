#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
#include "Global.h"
#include "Tile.h"

struct HolderCell 
{
	sf::RectangleShape cell;
	bool selected;

	HolderCell(const sf::Vector2f& position, float size) : selected(false) 
	{
		cell.setSize(sf::Vector2f(size, size));
		cell.setPosition(position);
		cell.setFillColor(sf::Color::Transparent);
		cell.setOutlineThickness(2.0f);
		cell.setOutlineColor(sf::Color::Black);
	}
};

class Board
{
public:
	Board();
	~Board();

	void render(sf::RenderWindow& m_window);
	void update();

	void toggleBag();
	void endTurn();

	void AITurn();
	void AIMultiplePlacements();

	int miniMax(int depth, bool maximizingPlayer);
	int evaluateBoard();
	void findBestMove();

	void selectedTile(sf::Vector2f mousePosition, int currentPlayer);

private:

	sf::Shape* tileShape;
	Tile currentTile;

	void initializeGrid();
	void fillBag();
	void randomTilesInHolder();

	void drawGridAndTileInHolder(sf::RenderWindow& m_window, const sf::RectangleShape& tileHolder, const std::vector<Tile>& tiles);
	void drawGridAndTilesInBag(sf::RenderWindow& m_window, const sf::RectangleShape& bagUI, const std::vector<Tile>& tileBag);

	bool isValidPlacement(sf::Vector2i gridPosition, int currentPlayer);
	bool checkAdjacentLines(sf::Vector2i gridPosition, const Tile& currentTile);
	bool checkLine(const sf::Vector2i& gridPosition, const Tile& currentTile, const sf::Vector2i& direction);

	sf::Vector2i getGridPosition(sf::Vector2f mousePosition);

	void setupUI();
	void setupFontAndText();
	void updateScores();

	int calculateScoreForPlacement(const sf::Vector2i& gridPosition, int currentPlayer);
	bool isSameTile(int y, int x, int currentPlayer);

	std::vector<std::vector<sf::RectangleShape>> gridRectangles; // main Board grid
	std::vector<Tile> tileBag;
	std::vector<Tile> tilesOnBoard;
	std::vector<Tile> player1Hands;
	std::vector<Tile> player2Hands;
	std::vector<HolderCell> cells;

	int row = 21;
	int col = 24;
	int player1Score = 0;
	int player2Score = 0;
	int selectedTileIndex = -1;
	int playerTurn;

	float tileSize = 50.0f;
	float posX;
	float posY;

	bool m_toggleBag = false;
	bool startingGame = true;
	bool tileSelected = false;
	bool ifAdjacentChecked = false;

	sf::Vector2i newGridPosition;

	sf::RectangleShape m_bottomUI;
	sf::RectangleShape m_seperationLineUI;
	sf::RectangleShape m_boxBagForTextUI;
	sf::RectangleShape m_tileHolder[2];
	sf::RectangleShape m_bagUI;

	sf::Font m_ArialBlackfont;

	sf::Text m_bagText;
	sf::Text m_player1ScoreText;
	sf::Text m_player2ScoreText;

};

