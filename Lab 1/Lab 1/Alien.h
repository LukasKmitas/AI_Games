#pragma once

#include <SFML/Graphics.hpp>

class Alien
{

public:
    Alien();
    ~Alien();

    void update(sf::Time t_deltaTime);
    void draw(sf::RenderWindow& m_window);

private:

    void setupAlien();
    void wrapAround();

    float getNewOrientation(float m_currentOrientation, sf::Vector2f m_velocity);
    void kinematicWander();

    sf::Vector2f normalize(sf::Vector2f vector);

    sf::Texture m_alienTexture;
    sf::Sprite m_alienSprite;

    sf::Vector2f m_velocity;
    float m_speed = 200.0f;
    float m_maxRotation = 0.05f;
    float m_orientation;
    sf::Vector2u m_windowSize = { 1200,800 };

};
