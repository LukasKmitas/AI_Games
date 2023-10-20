#pragma once
#include "SFML/Graphics.hpp"

class Tile 
{
public:

    sf::RectangleShape m_tile;
    bool isTraversable;
    sf::Vector2f m_position;
    sf::Vector2f m_flowField;
    int m_cost;
    int m_intergrationF;
};
