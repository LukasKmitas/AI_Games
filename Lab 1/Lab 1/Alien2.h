#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Alien2
{

public:
    Alien2();
    ~Alien2();

    Player m_player;

    void update(sf::Time t_deltaTime);
    void draw(sf::RenderWindow& m_window);

    void kinematicSeek(sf::Vector2f targetPosition);
    void kinematicArrive(sf::Vector2f targetPosition);

private:

    void setupAlien2();
    void wrapAround();

    float getNewOrientation(float m_currentOrientation, sf::Vector2f m_velocity);

    sf::Vector2f normalize(sf::Vector2f vector);

    float length(sf::Vector2f vector);

    sf::Texture m_alien2Texture;
    sf::Sprite m_alien2Sprite;

    sf::Vector2f m_velocity;
    float m_speed = 200.0f;
    float m_maxRotation = 45.0f;
    float m_orientation;
    float m_radius = 80.0f;
    float m_timeToTarget = 2.0f;
    sf::Vector2u m_windowSize = { 1200,800 };

};
