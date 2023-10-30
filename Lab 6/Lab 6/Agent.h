#pragma once
#include "SFML/Graphics.hpp"

class Agent
{
public:
    Agent();

    void update(sf::Time dt, const sf::Vector2i& goalTile);
    void setPosition(const sf::Vector2f& position);
    void render(sf::RenderWindow& window);

private:
    
    void moveAlongFlowField(const sf::Vector2i& goalTile);
    void setupAgent();

    sf::ConvexShape m_triangle;
    
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;

};