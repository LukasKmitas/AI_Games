#include "Agent.h"

Agent::Agent()
	: m_position(0.0f, 0.0f), m_velocity(0.0f, 0.0f)
{
    setupAgent();
}

void Agent::update(sf::Time dt, const sf::Vector2i& goalTile)
{
	moveAlongFlowField(goalTile);
}

void Agent::setPosition(const sf::Vector2f& position)
{
	m_position = position;
}

void Agent::render(sf::RenderWindow& window)
{
    window.draw(m_triangle);
}

void Agent::moveAlongFlowField(const sf::Vector2i& goalTile)
{
}

void Agent::setupAgent()
{
    m_triangle.setPointCount(3);
    m_triangle.setPoint(0, sf::Vector2f(0.0f, -20.0f));  // Top point
    m_triangle.setPoint(1, sf::Vector2f(-15.0f, 15.0f));  // Bottom-left point
    m_triangle.setPoint(2, sf::Vector2f(15.0f, 15.0f));   // Bottom-right point

    m_triangle.setFillColor(sf::Color::Red);
    m_triangle.setOutlineColor(sf::Color::Black);
    m_triangle.setOutlineThickness(2.0f);
}
