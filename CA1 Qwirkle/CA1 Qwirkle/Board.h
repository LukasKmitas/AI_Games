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

	void toggleBag();
	void endTurn();
	void selectedTile(sf::Vector2f mousePosition);

private:

	void initializeGrid();
	void fillBag();
	void randomTilesInHolder();

	void drawGridAndTileInHolder(sf::RenderWindow& m_window, const sf::RectangleShape& tileHolder, const std::vector<Tile>& tiles);
	void drawGridAndTilesInBag(sf::RenderWindow& m_window, const sf::RectangleShape& bagUI, const std::vector<Tile>& tileBag);

	bool isValidPlacement(sf::Vector2i gridPosition);
	void checkIfAdjacent();
	bool isValidColorLine(const std::vector<Tile>& line);
	bool isValidShapeLine(const std::vector<Tile>& line);

	sf::Vector2i getGridPosition(sf::Vector2f mousePosition);

	void setupUI();
	void setupFontAndText();

	std::vector<std::vector<sf::RectangleShape>> gridRectangles; // main Board grid
	std::vector<Tile> tileBag;
	std::vector<Tile> tilesOnBoard;
	std::vector<Tile> player1Hands;
	std::vector<Tile> Player2Hands;
	std::vector<HolderCell> cells;

	int row = 21;
	int col = 24;
	int selectedTileIndex = -1;
	float tileSize = 50.0f;
	bool m_toggleBag = false;
	bool startingGame = true;
	bool tileSelected = false;
	bool rulesChecked = false;

	sf::Vector2i newGridPosition;

	sf::RectangleShape m_bottomUI;
	sf::RectangleShape m_seperationLineUI;
	sf::RectangleShape m_boxBagForTextUI;
	sf::RectangleShape m_tileHolder[2];
	sf::RectangleShape m_bagUI;

	sf::Text m_bagText;
	sf::Font m_ArialBlackfont;

};

