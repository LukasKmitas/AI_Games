#pragma once

struct Global
{
public:
	static const int S_WIDTH{ 2000U };
	static const int S_HEIGHT{ 2000U };
	static const int TILE_SIZE{ std::min(S_WIDTH / 50, S_HEIGHT / 50) };
	static const int GRID_WIDTH{ S_WIDTH / TILE_SIZE };
	static const int GRID_HEIGHT{ S_HEIGHT / TILE_SIZE };
};