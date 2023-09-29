#include "EnemyPursue.h"

EnemyPursue::EnemyPursue()
{
	EnemyBase::setupEnemy();
	EnemyBase::setupConeOfVision();
	EnemyBase::setupFontAndText();

	m_enemySprite.setColor(sf::Color::Cyan);
	m_enemyTypeText.setString("PURSUE");
}

EnemyPursue::~EnemyPursue()
{
}

void EnemyPursue::update(sf::Time t_deltaTime, sf::Vector2f& playerPosition)
{
	EnemyBase::update(t_deltaTime, playerPosition);
}

void EnemyPursue::draw(sf::RenderWindow& m_window)
{
	EnemyBase::draw(m_window);
}

/// <summary>
/// A pursue to predict the players future position
/// to go to that position
/// </summary>
/// <param name="futurePlayerPosition"></param>
void EnemyPursue::pursue(sf::Vector2f futurePlayerPosition)
{
    sf::Vector2f direction = futurePlayerPosition - m_enemySprite.getPosition();
    float distance = length(direction);
    float speed = length(m_velocity);
    float timePrediction;

    if (speed <= distance / maxTimePrediction)
    {
        timePrediction = maxTimePrediction;
    }
    else
    {
        timePrediction = distance / speed;
    }

    sf::Vector2f newTargetPosition = futurePlayerPosition + (m_player.getVelocity() * timePrediction);

    SteeringOutput steering = getSteering(newTargetPosition);

    float newSpeed = length(steering.linear);
    if (newSpeed > maxSpeed)
    {
        steering.linear = normalize(steering.linear) * maxSpeed;
    }
    if (length(m_velocity) >= maxSpeed)
    {
        m_velocity = normalize(m_velocity) * maxSpeed;
    }
    m_velocity = steering.linear; 
    m_orientation = getNewOrientation(m_orientation, m_velocity);
}

/// <summary>
/// Gets the steering towards target
/// </summary>
/// <param name="targetPosition"></param>
/// <returns></returns>
SteeringOutput EnemyPursue::getSteering(sf::Vector2f targetPosition)
{
    SteeringOutput steering;

    sf::Vector2f desiredVelocity = targetPosition - m_enemySprite.getPosition();
    desiredVelocity = normalize(desiredVelocity);
    steering.linear = desiredVelocity * m_maxAcceleration;

    sf::Vector2f direction = steering.linear;
    float angle = atan2(direction.y, direction.x) * 180 / 3.14159265;
    steering.angular = angle;

    return steering;
}
