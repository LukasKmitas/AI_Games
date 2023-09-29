#pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "EnemyBase.h"
#include "Player.h"

class EnemyArriveFast : public EnemyBase
{
public:
    Player m_player;

    EnemyArriveFast();
    ~EnemyArriveFast();

    void update(sf::Time t_deltaTime, sf::Vector2f& playerPosition);
    void draw(sf::RenderWindow& m_window);

    void dynamicArrive(sf::Vector2f targetPosition);

    SteeringOutput getSteering(sf::Vector2f targetPosition);

private:

    float m_speed = 120.0f;

};

