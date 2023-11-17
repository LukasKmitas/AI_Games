#pragma once
#include <iostream>
#include <vector>
#include "Tile.h"

class Grid
{
public:
	Grid();
	~Grid();

private:

	std::vector<std::vector<Tile>> m_tiles;

};

