#include "EnemyWander.h"
#include <iostream>

EnemyWander::EnemyWander()
{
    EnemyBase::setupEnemy();
    EnemyBase::setupConeOfVision();
    EnemyBase::setupFontAndText();

    m_enemyTypeText.setString("Wander");
}

EnemyWander::~EnemyWander()
{
}

void EnemyWander::update(sf::Time t_deltaTime)
{
    SteeringOutput steering = getSteering();

    m_velocity += steering.linear;
    m_orientation = getNewOrientation(m_orientation, m_velocity);

    float randomRotation = (static_cast<float>(rand()) / RAND_MAX) * 50.0f - 1.0f;
    m_orientation += m_maxRotation * randomRotation;


    m_velocity = sf::Vector2f(-sin(m_orientation), cos(m_orientation)) * m_speed;

    dynamicWander();

    EnemyBase::update(t_deltaTime);
}

void EnemyWander::draw(sf::RenderWindow& m_window)
{
    EnemyBase::draw(m_window);
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

SteeringOutput EnemyWander::getSteering()
{
    SteeringOutput steering;

    sf::Vector2f desiredVelocity = sf::Vector2f(2000, 400) - m_enemySprite.getPosition();
    desiredVelocity = normalize(desiredVelocity);
    steering.linear = desiredVelocity * EnemyWander::m_maxAcceleration;
    
    steering.angular = 0;

    return steering;
}