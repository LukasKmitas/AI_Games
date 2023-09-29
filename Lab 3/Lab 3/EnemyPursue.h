#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "EnemyBase.h"
#include "Player.h"

class EnemyPursue : public EnemyBase
{
public:
    Player m_player;

    EnemyPursue();
    ~EnemyPursue();

    void update(sf::Time t_deltaTime, sf::Vector2f& playerPosition);
    void draw(sf::RenderWindow& m_window);

    void pursue(sf::Vector2f targetPosition);

    SteeringOutput getSteering(sf::Vector2f targetPosition);

private:

    float m_speed = 60.0f;
    float maxSpeed = 100.0f;
    float m_maxRotation = 45.0f;

};

