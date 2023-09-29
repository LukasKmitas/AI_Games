#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "EnemyBase.h"

class EnemyWander : public EnemyBase
{
public:
	EnemyWander();
	~EnemyWander();

	void update(sf::Time t_deltaTime) override;
	void draw(sf::RenderWindow& m_window) override;

private:

	void dynamicWander();

	SteeringOutput getSteering();

	float m_maxRotation = 0.05f;
	float m_speed = 100.0f;

};

