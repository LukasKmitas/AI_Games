#include "Alien3.h"
#include <iostream>

Alien3::Alien3()
{
	setupAlien3();
}

Alien3::~Alien3()
{
}

void Alien3::update(sf::Time t_deltaTime)
{
    float deltaTimeSec = t_deltaTime.asSeconds();

    wrapAround();

    m_alien3Sprite.move(m_velocity * deltaTimeSec);
}

void Alien3::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_alien3Sprite);
}

void Alien3::kinematicFlee(sf::Vector2f targetPosition)
{
    m_velocity = m_alien3Sprite.getPosition() - targetPosition;

    float distance = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
    if (distance < m_radius)
    {
        m_velocity = normalize(m_velocity);
        m_velocity = m_velocity * m_speed;
        m_orientation = getNewOrientation(m_orientation, m_velocity);
    }
    else
    {
        m_velocity = sf::Vector2f(0.0f, 0.0f);
    }
}

void Alien3::setupAlien3()
{
	if (!m_alien3Texture.loadFromFile("Assets\\Images\\alien3.png"))
	{
		std::cout << "problem loading logo" << std::endl;
	}
	m_alien3Sprite.setTexture(m_alien3Texture);
	m_alien3Sprite.setPosition(1000.0f, 100.0f);
	m_alien3Sprite.setOrigin(185, 185);
	m_alien3Sprite.setScale(0.4, 0.4);
}

void Alien3::wrapAround()
{
    if (m_alien3Sprite.getPosition().x < 0)
    {
        m_alien3Sprite.setPosition(m_windowSize.x, m_alien3Sprite.getPosition().y);
    }
    else if (m_alien3Sprite.getPosition().x > m_windowSize.x)
    {
        m_alien3Sprite.setPosition(0, m_alien3Sprite.getPosition().y);
    }

    if (m_alien3Sprite.getPosition().y < 0)
    {
        m_alien3Sprite.setPosition(m_alien3Sprite.getPosition().x, m_windowSize.y);
    }
    else if (m_alien3Sprite.getPosition().y > m_windowSize.y)
    {
        m_alien3Sprite.setPosition(m_alien3Sprite.getPosition().x, 0);
    }
}

float Alien3::getNewOrientation(float m_currentOrientation, sf::Vector2f m_velocity)
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

sf::Vector2f Alien3::normalize(sf::Vector2f vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
    {
        vector.x /= length;
        vector.y /= length;
    }
    return vector;
}
