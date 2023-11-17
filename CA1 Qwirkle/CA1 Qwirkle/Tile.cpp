#include "Tile.h"

Tile::Tile()
{
}

void Tile::setShape(TileShape shape)
{
	m_shape = shape;
	if (shape == TileShape::Circle)
	{

	}
}

void Tile::setColor(TileColor color)
{
}

TileShape Tile::getShape() const
{
	return TileShape();
}

TileColor Tile::getColor() const
{
	return TileColor();
}
