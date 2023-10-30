#pragma once
#include <vector>
#include <iostream>
#include "Tile.h"
#include "Global.h"

class Grid
{
public:
	Grid();

	void render(sf::RenderWindow& window);

	Tile& getTile(int row, int col);

	void setTileCost(int row, int col, int cost);
	void setTileTraversable(int row, int col, bool traversable);
	void toggleTextDisplay();

	void setStartTile(const sf::Vector2i& startTile);
	void setGoalTile(const sf::Vector2i& goalTile);
	void setObstacleTile(const sf::Vector2i& obstacleTile);

	void setCostField();
	void calculateVectorField();

private:

	void setupFontAndText();

	const double PI = 3.14159265358979323846;

	std::vector<std::vector<Tile>> m_tiles;
	sf::Vector2i m_startTile;
	sf::Vector2i m_goalTile;
	sf::Vector2i m_currentStartTile;
	sf::Vector2i m_currentGoalTile;
	sf::Vector2i m_currentObstacleTile;

	sf::Font m_ArialBlackfont;
	sf::Text m_tileNumberText;

	int tileNumber = 1;
	float scalingFactor = 2.0f;

	bool m_displayText;

};