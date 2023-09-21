#include "Alien.h"
#include <iostream>
#include <cmath>

Alien::Alien()
{
	setupAlien();
}

Alien::~Alien()
{
}

void Alien::update(sf::Time t_deltaTime)
{
    float deltaTimeSec = t_deltaTime.asSeconds();

    kinematicWander();
    wrapAround();

    m_alienSprite.move(m_velocity * deltaTimeSec);
}

void Alien::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_alienSprite);
}

void Alien::setupAlien()
{
	if (!m_alienTexture.loadFromFile("Assets\\Images\\alien.png"))
	{
		std::cout << "problem loading logo" << std::endl;
	}
	m_alienSprite.setTexture(m_alienTexture);
	m_alienSprite.setPosition(600.0f, 400.0f);
	m_alienSprite.setOrigin(700, 700);
	m_alienSprite.setScale(0.1, 0.1);
}

void Alien::wrapAround()
{
    if (m_alienSprite.getPosition().x < 0)
    {
        m_alienSprite.setPosition(m_windowSize.x, m_alienSprite.getPosition().y);
    }
    else if (m_alienSprite.getPosition().x > m_windowSize.x)
    {
        m_alienSprite.setPosition(0, m_alienSprite.getPosition().y);
    }

    if (m_alienSprite.getPosition().y < 0)
    {
        m_alienSprite.setPosition(m_alienSprite.getPosition().x, m_windowSize.y);
    }
    else if (m_alienSprite.getPosition().y > m_windowSize.y)
    {
        m_alienSprite.setPosition(m_alienSprite.getPosition().x, 0);
    }
}

float Alien::getNewOrientation(float m_currentOrientation, sf::Vector2f m_velocity)
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

/// <summary>
/// To make the Alien meander to its target
/// </summary>
void Alien::kinematicWander()
{
    m_velocity = sf::Vector2f{ 2000, 400 } - m_alienSprite.getPosition();
    m_velocity = normalize(m_velocity);
    m_orientation = getNewOrientation(m_orientation, m_velocity);

    float randomRotation = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;
    m_orientation += m_maxRotation * randomRotation;

    m_velocity = sf::Vector2f(-sin(m_orientation), cos(m_orientation)) * m_speed;
}

/// <summary>
/// Version 2
/// </summary>
//void Alien::kinematicWander()
//{
//    sf::Vector2f m_target(1.0f, 0.0f);
//
//    sf::Vector2f meanderForce = sf::Vector2f(
//        (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f,
//        (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f
//    );
//
//    meanderForce = normalize(meanderForce);
//    m_velocity = (m_target + meanderForce) * m_speed;
//
//    m_orientation = getNewOrientation(m_orientation, m_velocity);
//}


sf::Vector2f Alien::normalize(sf::Vector2f vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
    {
        vector.x /= length;
        vector.y /= length;
    }
    return vector;
}
