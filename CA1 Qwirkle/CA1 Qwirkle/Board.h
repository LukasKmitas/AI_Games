#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "Tile.h"

class Board
{
public:
	Board();
	~Board();

	void render(sf::RenderWindow& m_window);

private:

	void initializeGrid();
	void populateGridRandomly();

	std::vector<std::vector<Tile>> m_tiles;

	int row = 10;
	int col = 10;
	float tileSize = 50.0f;
};

