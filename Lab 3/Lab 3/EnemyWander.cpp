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

void EnemyWander::update(sf::Time t_deltaTime, sf::Vector2f& playerPosition)
{
    SteeringOutput steering = getSteering();

    m_velocity += steering.linear;
    m_orientation = getNewOrientation(m_orientation, m_velocity);

    float randomRotation = (static_cast<float>(rand()) / RAND_MAX) * 50.0f - 1.0f;
    m_orientation += m_maxRotation * randomRotation;


    m_velocity = sf::Vector2f(-sin(m_orientation), cos(m_orientation)) * m_speed;

    dynamicWander();

    EnemyBase::update(t_deltaTime, playerPosition);
}

void EnemyWander::draw(sf::RenderWindow& m_window)
{
    EnemyBase::draw(m_window);
}

/// <summary>
/// Dynamic Wander
/// it makes the enemy wander 
/// </summary>
void EnemyWander::dynamicWander()
{
    m_velocity = sf::Vector2f{ 2000, 400 } - m_enemySprite.getPosition();
    m_velocity = normalize(m_velocity);
    m_orientation = getNewOrientation(m_orientation, m_velocity);

    float randomRotation = (static_cast<float>(rand()) / RAND_MAX) * 2.0f - 1.0f;
    m_orientation += m_maxRotation * randomRotation;

    m_velocity = sf::Vector2f(-sin(m_orientation), cos(m_orientation)) * m_speed;
}

/// <summary>
/// gets a steering 
/// </summary>
/// <returns></returns>
SteeringOutput EnemyWander::getSteering()
{
    SteeringOutput steering;

    sf::Vector2f desiredVelocity = sf::Vector2f(2000, 400) - m_enemySprite.getPosition();
    desiredVelocity = normalize(desiredVelocity);
    steering.linear = desiredVelocity * EnemyWander::m_maxAcceleration;
    
    sf::Vector2f direction = steering.linear;
    float angle = atan2(direction.y, direction.x) * 180 / 3.14159265;
    steering.angular = angle;

    return steering;
}