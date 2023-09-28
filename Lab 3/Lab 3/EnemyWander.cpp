#include "EnemyWander.h"
#include <iostream>

EnemyWander::EnemyWander()
{
	setupEnemy();
}

EnemyWander::~EnemyWander()
{
}

void EnemyWander::update(sf::Time t_deltaTime)
{
    float deltaTimeSec = t_deltaTime.asSeconds();

    dynamicWander();
    wrapAround();

    m_enemySprite.move(m_velocity * deltaTimeSec);
}

void EnemyWander::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_enemySprite);
}

void EnemyWander::setupEnemy()
{
    if (!m_enemyTexture.loadFromFile("Assets\\Images\\Enemy_Pirate.png"))
    {
        std::cout << "problem loading image" << std::endl;
    }
    m_enemyTexture.setSmooth(true);
    m_enemySprite.setTexture(m_enemyTexture);
    m_enemySprite.setPosition(600.0f, 100.0f);
    m_enemySprite.setOrigin(m_enemySprite.getTextureRect().width / 2, m_enemySprite.getTextureRect().height / 2);
    m_enemySprite.setScale(0.3, 0.3);
}

void EnemyWander::wrapAround()
{
    if (m_enemySprite.getPosition().x < 0)
    {
        m_enemySprite.setPosition(ScreenSize::s_width, m_enemySprite.getPosition().y);
    }
    else if (m_enemySprite.getPosition().x > ScreenSize::s_width)
    {
        m_enemySprite.setPosition(0, m_enemySprite.getPosition().y);
    }

    if (m_enemySprite.getPosition().y < 0)
    {
        m_enemySprite.setPosition(m_enemySprite.getPosition().x, ScreenSize::s_height);
    }
    else if (m_enemySprite.getPosition().y > ScreenSize::s_height)
    {
        m_enemySprite.setPosition(m_enemySprite.getPosition().x, 0);
    }
}

void EnemyWander::dynamicWander()
{
    m_velocity = sf::Vector2f{ 2000, 400 } - m_enemySprite.getPosition();
    m_velocity = normalize(m_velocity);
    m_orientation = getNewOrientation(m_orientation, m_velocity);

    float randomRotation = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;
    m_orientation += m_maxRotation * randomRotation;

    m_velocity = sf::Vector2f(-sin(m_orientation), cos(m_orientation)) * m_speed;
}

float EnemyWander::getNewOrientation(float m_currentOrientation, sf::Vector2f m_velocity)
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

sf::Vector2f EnemyWander::normalize(sf::Vector2f vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
    {
        vector.x /= length;
        vector.y /= length;
    }
    return vector;
}

