#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "Global.h"
#include "Tile.h"

class Board
{
public:
	Board();
	~Board();

	void render(sf::RenderWindow& m_window);

	void toggleBag();

private:

	void initializeGrid();
	void initializeTileHolderGrid(sf::RenderWindow& m_window, const sf::RectangleShape& tileHolder);

	void fillBag();
	void randomTilesInHolder();

	void drawGridAndTilesInBag(sf::RenderWindow& m_window, const sf::RectangleShape& bagUI, const std::vector<Tile>& tileBag);

	void setupUI();
	void setupFontAndText();

	std::vector<std::vector<sf::RectangleShape>> gridRectangles;
	std::vector<Tile> tileBag;

	int row = 21;
	int col = 24;
	float tileSize = 50.0f;
	bool m_toggleBag = false;

	sf::RectangleShape m_bottomUI;
	sf::RectangleShape m_seperationLineUI;
	sf::RectangleShape m_boxBagForTextUI;
	sf::RectangleShape m_tileHolder[2];
	sf::RectangleShape m_bagUI;

	sf::Text m_bagText;
	sf::Font m_ArialBlackfont;

};

