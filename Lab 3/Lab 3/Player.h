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

private:

    void setupPlayer();
    void movement();
    void wrapAround();

    sf::Vector2f normalize(sf::Vector2f vector);
    float length(sf::Vector2f vector);

    sf::Texture m_playerTexture;
    sf::Sprite m_playerSprite;

    sf::Vector2f m_velocity;

    float m_acceleration = 10.0f;
    float m_deceleration = 20.0f;
    float m_maxAceleration = 30.0f;
    float m_speed = 200;
    float m_maxSpeed = 200;
    float m_turnSpeed = 10;
    float m_rotation;

};

