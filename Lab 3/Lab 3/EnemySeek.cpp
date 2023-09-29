#include <iostream>
#include "EnemySeek.h"

EnemySeek::EnemySeek()
{
	EnemyBase::setupEnemy();
	EnemyBase::setupConeOfVision();
	EnemyBase::setupFontAndText();

	m_enemySprite.setColor(sf::Color::Red);
	m_enemyTypeText.setString("SEEK");
}

EnemySeek::~EnemySeek()
{
}

void EnemySeek::update(sf::Time t_deltaTime, sf::Vector2f& playerPosition)
{
	EnemyBase::update(t_deltaTime, playerPosition);

	SteeringOutput steering = getSteering(sf::Vector2f(m_player.getPosition()));

	m_velocity += steering.linear;
	m_orientation = getNewOrientation(m_orientation, m_velocity);

	if (detectPlayer(playerPosition))
	{
		m_coneOfVision.setFillColor(sf::Color(255, 0, 0, 200));
	}
	else
	{
		m_coneOfVision.setFillColor(sf::Color(0, 0, 0, 100));
	}
}

void EnemySeek::draw(sf::RenderWindow& m_window)
{
	EnemyBase::draw(m_window);
}

void EnemySeek::dynamicSeek(sf::Vector2f targetPosition)
{
	m_velocity = targetPosition - m_enemySprite.getPosition();
	m_velocity = normalize(m_velocity);
	m_velocity = m_velocity * m_speed;

	m_orientation = getNewOrientation(m_orientation, m_velocity);
}

bool EnemySeek::detectPlayer(sf::Vector2f playerPosition)
{
	sf::Vector2f m_playerPosition = m_player.getPosition();
	sf::Vector2f toPlayer = playerPosition - m_enemySprite.getPosition();

	float angleToPlayer = std::atan2(toPlayer.y, toPlayer.x) * 180.0f / 3.14159265f;

	if (angleToPlayer < 0)
	{
		angleToPlayer += 360.0f;
	}

	float angleDifference = std::abs(angleToPlayer - m_enemySprite.getRotation());

	if (angleDifference <= m_visionAngle / 2.0f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

SteeringOutput EnemySeek::getSteering(sf::Vector2f targetPosition)
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