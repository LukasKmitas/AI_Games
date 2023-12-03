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
    ~Tile();

    void setShape(TileShape shape);
    void setColor(TileColor color);

    sf::Shape* getTileShape() const;

    void setPosition(const sf::Vector2i& newPosition);

    sf::Vector2i getPosition() const
    {
        return position;
    }
    TileShape getShape() const 
    {
        return m_shape;
    }
    TileColor getColor() const 
    {
        return m_color;
    }

    std::string getShapeAsString() const;
    std::string getColorAsString() const;

    TileShape m_shape;
    TileColor m_color;

private:

    sf::Shape* m_tileShape;

    void createTileShape();

    sf::Vector2i position;

    bool m_isPlaced;

};