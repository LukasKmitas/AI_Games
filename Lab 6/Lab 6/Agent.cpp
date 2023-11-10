#include "Agent.h"

Agent::Agent(Grid& grid)
    : 
    m_grid(grid)
{
    setupAgent();
    m_currentPathIndex = 0;
    m_speed = 50;
}

void Agent::update(sf::Time dt)
{
    if (m_togglePath)
    {
        // vector path
        // That kinda uses flowfield
        m_path = m_grid.getPath();
        if (!m_path.empty() && m_currentPathIndex < m_path.size())
        {
            sf::Vector2f targetPosition = m_grid.getPositionInTile(m_path[m_currentPathIndex]);
            sf::Vector2f direction = targetPosition - m_position;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance < 1.0f)
            {
                m_currentPathIndex++;
            }
            else
            {
                direction /= distance;
                m_position += direction * m_speed * dt.asSeconds();
                m_circle.setPosition(m_position);
            }
        }
    }
    else
    {
        // With flowfield
        int col = static_cast<int>(m_position.x / Global::TILE_SIZE);
        int row = static_cast<int>(m_position.y / Global::TILE_SIZE);

        if (col >= 0 && col < Global::GRID_WIDTH && row >= 0 && row < Global::GRID_HEIGHT) 
        {
            sf::Vector2f flowField = m_grid.getTile(row, col).m_flowField;

            m_position += flowField * m_speed * dt.asSeconds();
            m_circle.setPosition(m_position);
        }
    }
}

void Agent::render(sf::RenderWindow& window)
{
    m_shader.setUniform("time", m_clock.getElapsedTime().asSeconds());
    window.draw(m_circle, &m_shader);
}

void Agent::togglePath()
{
    m_togglePath = !m_togglePath;
}

void Agent::setupAgent()
{
    if (!m_texture.loadFromFile("ASSETS\\IMAGES\\Sparkle.png"))
    {
        std::cerr << "Failed to load texture" << std::endl;
    }
    if (!m_shader.loadFromFile("ASSETS\\SHADERS\\sparkle_shader.frag", sf::Shader::Fragment))
    {
        std::cerr << "Failed to load shader" << std::endl;
    }

    m_circle.setRadius(20.0f);
    m_circle.setFillColor(sf::Color::Red);
    m_shader.setUniform("texture", m_texture);
    m_clock.restart();
}
