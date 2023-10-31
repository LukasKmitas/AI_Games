#pragma once
#include <vector>
#include <iostream>
#include "Tile.h"
#include "Global.h"
#include <queue>

struct IntegrationFieldComparator
{
	bool operator()(const Tile* lhs, const Tile* rhs) const
	{
		return lhs->m_integrationF > rhs->m_integrationF;
	}
};

class Grid
{
public:
	Grid();

	void render(sf::RenderWindow& window);

	Tile& getTile(int row, int col);

	void setTileCost(int row, int col, int cost);
	void setTileTraversable(int row, int col, bool traversable);

	void toggleTextDisplay();
	void toggleCostDisplay();
	void toggleIntegrationFieldDisplay();
	void togglePathDisplay();

	void setStartTile(const sf::Vector2i& startTile);
	void setGoalTile(const sf::Vector2i& goalTile);
	void setObstacleTile(const sf::Vector2i& obstacleTile);

	void calculateCostField();
	void calculateIntegrationField();
	void calculateVectorField();

	std::vector<sf::Vector2i> getPath() const;
	sf::Vector2f getPositionInTile(const sf::Vector2i& tile) const;

private:

	void setupFontAndText();

	const double PI = 3.14159265358979323846;

	std::vector<std::vector<Tile>> m_tiles;
	std::vector<sf::Vector2i> m_path;
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
	bool m_displayCost;
	bool m_displayIntegrationField;
	bool m_displayPath;

};