#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"

class Player
{
public:
    Player();
    ~Player();

    void update(sf::Time t_deltaTime);
    void draw(sf::RenderWindow& m_window);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;

    bool detectEnemy();

private:

    void setupPlayer();
    void setupConeOfVision();;

    void movement();
    void wrapAround();
    void coneOfVision();

    sf::Vector2f normalize(sf::Vector2f vector);
    float length(sf::Vector2f vector);
    float toRadians(float degrees);

    sf::Texture m_playerTexture;
    sf::Sprite m_playerSprite;

    sf::ConvexShape m_coneOfVision;

    sf::Vector2f m_velocity;

    sf::VertexArray m_directionLine{ sf::Lines, 2 };

    float m_acceleration = 10.0f;
    float m_deceleration = 20.0f;
    float m_maxAceleration = 200.0f;
    float m_speed = 150.0f;
    float m_maxSpeed = 200.0f;
    float m_turnSpeed = 10.0f;
    float m_rotationSpeed = 3.0f;
    float m_coneRotation = 0.0f;

    bool m_enemyDetected = false;
    float detectionDistanceThreshold = 150.0f; 
    float detectionAngleThreshold = 50.0f;

};

