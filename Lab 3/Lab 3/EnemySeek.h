#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "EnemyBase.h"
#include "Player.h"

class EnemySeek : public EnemyBase
{

public:
    Player m_player;

    EnemySeek();
    ~EnemySeek();

    void update(sf::Time t_deltaTime, sf::Vector2f& playerPosition) override;
    void draw(sf::RenderWindow& m_window) override;

    void dynamicSeek(sf::Vector2f targetPosition);

    bool detectPlayer(sf::Vector2f playerPosition);

    SteeringOutput getSteering(sf::Vector2f targetPosition);

private:

    float m_speed = 100.0f;
    float m_maxRotation = 45.0f;
    float m_radius = 80.0f;
    float m_timeToTarget = 2.0f;

};

