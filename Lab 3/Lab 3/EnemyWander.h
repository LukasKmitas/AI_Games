#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"

class EnemyWander
{
public:
	EnemyWander();
	~EnemyWander();

	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& m_window);

private:

	void setupEnemy();
	void wrapAround();

	void dynamicWander();

	float getNewOrientation(float m_currentOrientation, sf::Vector2f m_velocity);
	sf::Vector2f normalize(sf::Vector2f vector);

	sf::Texture m_enemyTexture;
	sf::Sprite m_enemySprite;

	sf::Vector2f m_velocity;
	float m_orientation;
	float wanderOrientation;
	float m_maxRotation = 0.05f;
	float m_speed = 200.0f;

	float wanderOffset = 100.0f;
	float wanderRadius = 50.0f;
	float wanderRate = 1.0f;
	float maxAcc = 200;

};

