#pragma once
#include "SFML/Graphics.hpp"

enum class TileShape 
{
    Empty,
    Circle,
    Square,
    Diamond,
    Club,
    Star,
    Cross
};

enum class TileColor 
{
    Empty,
    Red,
    Orange,
    Yellow,
    Green,
    Blue,
    Purple
};

class Tile
{
public:

    Tile();

    void setShape(TileShape shape);
    void setColor(TileColor color);
    TileShape getShape() const;
    TileColor getColor() const;

private:

    sf::RectangleShape m_tile;
    TileShape m_shape;
    TileColor m_color;
    bool m_isPlaced;

};