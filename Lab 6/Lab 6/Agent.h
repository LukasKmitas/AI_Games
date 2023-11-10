#pragma once
#include "SFML/Graphics.hpp"
#include "Grid.h"

class Agent
{
public:
    Agent(Grid& grid);

    void update(sf::Time dt);
    void render(sf::RenderWindow& window);

    void togglePath();

private:
    
    void setupAgent();

    Grid& m_grid;
    std::vector<sf::Vector2i> m_path;

    sf::Vector2f m_position;
    sf::CircleShape m_circle;
    sf::Clock m_clock;
    sf::Shader m_shader;
    sf::Texture m_texture;

    bool m_togglePath;
    int m_currentPathIndex;
    float m_speed;
    const double PI = 3.14159265358979323846;

};