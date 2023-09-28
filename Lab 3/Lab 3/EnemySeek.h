#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ScreenSize.h"

class EnemySeek
{

public:
    EnemySeek();
    ~EnemySeek();

    Player m_player;

    void update(sf::Time t_deltaTime);
    void draw(sf::RenderWindow& m_window);

private:

    void setupEnemy();
    void wrapAround();

    void kinematicSeek(sf::Vector2f targetPosition);

    float getNewOrientation(float m_currentOrientation, sf::Vector2f m_velocity);
    sf::Vector2f normalize(sf::Vector2f vector);
    float length(sf::Vector2f vector);

    sf::Texture m_enemyTexture;
    sf::Sprite m_enemySprite;

    sf::Vector2f m_velocity;
    float m_speed = 200.0f;
    float m_maxRotation = 45.0f;
    float m_orientation = 0;
    float m_radius = 80.0f;
    float m_timeToTarget = 2.0f;

};

