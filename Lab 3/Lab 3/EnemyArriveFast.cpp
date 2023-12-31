#include "EnemyArriveFast.h"
#include <iostream>

EnemyArriveFast::EnemyArriveFast()
{
	EnemyBase::setupEnemy();
	EnemyBase::setupConeOfVision();
    EnemyBase::setupFontAndText();

	m_enemySprite.setColor(sf::Color::Blue);
    m_enemyTypeText.setString("Arrive Fast");
}

EnemyArriveFast::~EnemyArriveFast()
{
}

void EnemyArriveFast::update(sf::Time t_deltaTime, sf::Vector2f& playerPosition)
{
    EnemyBase::update(t_deltaTime, playerPosition);

    SteeringOutput steering = getSteering(sf::Vector2f(m_player.getPosition()));

    m_velocity += steering.linear;
    m_orientation = getNewOrientation(m_orientation, m_velocity);
}

void EnemyArriveFast::draw(sf::RenderWindow& m_window)
{
	EnemyBase::draw(m_window);
}

/// <summary>
/// To make a dynamic Arrive 
/// So it follows the player and it slows and stop within a certain radius
/// </summary>
/// <param name="targetPosition"></param>
void EnemyArriveFast::dynamicArrive(sf::Vector2f targetPosition)
{
	m_velocity = targetPosition - m_enemySprite.getPosition();

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

/// <summary>
/// Gets the steering 
/// </summary>
/// <param name="targetPosition"></param>
/// <returns></returns>
SteeringOutput EnemyArriveFast::getSteering(sf::Vector2f targetPosition)
{
    SteeringOutput steering;

    sf::Vector2f desiredVelocity = targetPosition - m_enemySprite.getPosition();

    float distance = std::sqrt(desiredVelocity.x * desiredVelocity.x + desiredVelocity.y * desiredVelocity.y);

    if (distance < m_radius)
    {
        steering.linear = sf::Vector2f(0.0f, 0.0f);
    }
    else
    {
        desiredVelocity /= m_timeToTarget;

        float speed = std::sqrt(desiredVelocity.x * desiredVelocity.x + desiredVelocity.y * desiredVelocity.y);
        if (speed > m_speed)
        {
            desiredVelocity = normalize(desiredVelocity);
            desiredVelocity *= m_speed;
        }
        steering.linear = desiredVelocity - m_velocity;
    }
    steering.angular = 0;

    return steering;
}