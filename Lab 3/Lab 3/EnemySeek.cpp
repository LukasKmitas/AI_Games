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