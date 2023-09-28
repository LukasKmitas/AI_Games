#include <iostream>
#include "EnemySeek.h"

EnemySeek::EnemySeek()
{
	setupEnemy();
}

EnemySeek::~EnemySeek()
{
}

void EnemySeek::update(sf::Time t_deltaTime)
{
}

void EnemySeek::draw(sf::RenderWindow& m_window)
{
}

void EnemySeek::setupEnemy()
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

void EnemySeek::wrapAround()
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

void EnemySeek::kinematicSeek(sf::Vector2f targetPosition)
{
	m_velocity = targetPosition - m_enemySprite.getPosition();
	m_velocity = normalize(m_velocity);
	m_velocity = m_velocity * m_speed;

	m_orientation = getNewOrientation(m_orientation, m_velocity);
}

float EnemySeek::getNewOrientation(float m_currentOrientation, sf::Vector2f m_velocity)
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

sf::Vector2f EnemySeek::normalize(sf::Vector2f vector)
{
	float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
	if (length != 0)
	{
		vector.x /= length;
		vector.y /= length;
	}
	return vector;
}

float EnemySeek::length(sf::Vector2f vector)
{
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}
