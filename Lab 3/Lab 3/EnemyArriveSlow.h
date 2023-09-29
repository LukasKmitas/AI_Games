#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "EnemyBase.h"
#include "Player.h"

class EnemyArriveSlow : public EnemyBase
{
public:
    Player m_player;

    EnemyArriveSlow();
    ~EnemyArriveSlow();

    void update(sf::Time t_deltaTime);
    void draw(sf::RenderWindow& m_window);

    void dynamicArrive(sf::Vector2f targetPosition);

    SteeringOutput getSteering(sf::Vector2f targetPosition);

private:

    float m_speed = 60.0f;
    float m_maxRotation = 45.0f;
    float m_radius = 80.0f;
    float m_timeToTarget = 2.0f;

};

