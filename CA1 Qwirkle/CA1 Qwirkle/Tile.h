#pragma once
#include "SFML/Graphics.hpp"

enum class TileShape 
{
    Empty,
    Circle,
    Square,
    Diamond,
    Clover,
    EightStar,
    FourthStar
};

enum class TileColor 
{
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
    ~Tile();

    void setShape(TileShape shape);
    void setColor(TileColor color);
    sf::Shape* getTileShape() const;

private:

    TileShape m_shape;
    TileColor m_color;

    sf::Shape* m_tileShape;

    void createTileShape();


    bool m_isPlaced;

};