#pragma once
#include "SFML/Graphics.hpp"

class Tile 
{
public:

    sf::RectangleShape m_tile;
    sf::Vector2f m_position;
    sf::Vector2f m_flowField;
    sf::Color m_vectorColor;
    int m_cost;
    int m_integrationF;
    int m_number;
    bool isTraversable;
};