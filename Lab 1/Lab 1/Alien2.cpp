#include "Alien2.h"
#include <iostream>

Alien2::Alien2()
{
	setupAlien2();
}

Alien2::~Alien2()
{
}

void Alien2::update(sf::Time t_deltaTime)
{
    float deltaTimeSec = t_deltaTime.asSeconds();

    //sf::Vector2f targetPosition = sf::Vector2f(200.0f, 200.0f);
    //kinematicSeek(targetPosition);
    //kinematicArrive(targetPosition);
    wrapAround();

    m_alien2Sprite.move(m_velocity * deltaTimeSec);
}

void Alien2::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_alien2Sprite);
}

void Alien2::setupAlien2()
{
	if (!m_alien2Texture.loadFromFile("Assets\\Images\\alien2.png"))
	{
		std::cout << "problem loading logo" << std::endl;
	}
	m_alien2Sprite.setTexture(m_alien2Texture);
	m_alien2Sprite.setPosition(1000.0f, 100.0f);
	m_alien2Sprite.setOrigin(146, 146);
	m_alien2Sprite.setScale(0.5, 0.5);
}

void Alien2::wrapAround()
{
    if (m_alien2Sprite.getPosition().x < 0)
    {
        m_alien2Sprite.setPosition(m_windowSize.x, m_alien2Sprite.getPosition().y);
    }
    else if (m_alien2Sprite.getPosition().x > m_windowSize.x)
    {
        m_alien2Sprite.setPosition(0, m_alien2Sprite.getPosition().y);
    }

    if (m_alien2Sprite.getPosition().y < 0)
    {
        m_alien2Sprite.setPosition(m_alien2Sprite.getPosition().x, m_windowSize.y);
    }
    else if (m_alien2Sprite.getPosition().y > m_windowSize.y)
    {
        m_alien2Sprite.setPosition(m_alien2Sprite.getPosition().x, 0);
    }
}

float Alien2::getNewOrientation(float m_currentOrientation, sf::Vector2f m_velocity)
{
    if (std::abs(m_velocity.x) > 0 || std::abs(m_velocity.y) > 0)
    {
        return std::atan2(m_velocity.y, m_velocity.x);
    }
    else
    {
        return m_currentOrientation;
    }
}

sf::Vector2f Alien2::normalize(sf::Vector2f vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
    {
        vector.x /= length;
        vector.y /= length;
    }
    return vector;
}

void Alien2::kinematicSeek(sf::Vector2f targetPosition)
{
    m_velocity = targetPosition - m_alien2Sprite.getPosition();
    m_velocity = normalize(m_velocity);
    m_velocity = m_velocity * m_speed;

    m_orientation = getNewOrientation(m_orientation, m_velocity);
}

void Alien2::kinematicArrive(sf::Vector2f targetPosition)
{
    m_velocity = targetPosition - m_alien2Sprite.getPosition();

    float distance = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
    if (distance < m_radius)
    {
        m_velocity = sf::Vector2f(0.0f, 0.0f);
    }
    else
    {
        m_velocity = m_velocity / m_timeToTarget;

        float speed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
        if (speed > m_speed)
        {
            m_velocity = normalize(m_velocity);
            m_velocity = m_velocity * m_speed;
        }
    }
    m_orientation = getNewOrientation(m_orientation, m_velocity);
}

float Alien2::length(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}


