#pragma once

#include <SFML/Graphics.hpp>

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

    sf::Texture m_playerTexture;
    sf::Sprite m_playerSprite;

    sf::Vector2f m_velocity;
    float m_speed = 200;
    sf::Vector2u m_windowSize = { 1200,800 };

};
