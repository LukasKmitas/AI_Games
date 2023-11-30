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
	void fillBag();
	void randomTilesInHolder();

	void drawGridAndTileInHolder(sf::RenderWindow& m_window, const sf::RectangleShape& tileHolder, const std::vector<Tile>& tiles);
	void drawGridAndTilesInBag(sf::RenderWindow& m_window, const sf::RectangleShape& bagUI, const std::vector<Tile>& tileBag);

	void setupUI();
	void setupFontAndText();

	std::vector<std::vector<sf::RectangleShape>> gridRectangles;
	std::vector<Tile> tileBag;
	std::vector<Tile> player1Hands;
	std::vector<Tile> Player2Hands;

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

