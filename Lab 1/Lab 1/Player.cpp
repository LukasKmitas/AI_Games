#include "Player.h"
#include <iostream>

Player::Player()
{
	setupPlayer();
}

Player::~Player()
{
}

void Player::update(sf::Time t_deltaTime)
{
    float deltaTimeSec = t_deltaTime.asSeconds();

	movement();
    wrapAround();

    m_playerSprite.move(m_velocity * deltaTimeSec);
}

void Player::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_playerSprite);
}

sf::Vector2f Player::getPosition() const
{
    return m_playerSprite.getPosition();
}

void Player::setupPlayer()
{
	if (!m_playerTexture.loadFromFile("Assets\\Images\\playerS.png"))
	{
		std::cout << "problem loading logo" << std::endl;
	}
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setPosition(350.0f, 400.0f);
    m_playerSprite.setOrigin(95, 95);
	m_playerSprite.setScale(0.5, 0.5);
}

void Player::movement()
{
    m_velocity = sf::Vector2f(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_velocity.x = -m_speed;
        m_playerSprite.setRotation(-90);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_velocity.x = m_speed;
        m_playerSprite.setRotation(90);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_velocity.y = -m_speed;
        m_playerSprite.setRotation(0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_velocity.y = m_speed;
        m_playerSprite.setRotation(180);
    }
}

void Player::wrapAround()
{
    if (m_playerSprite.getPosition().x < 0)
    {
        m_playerSprite.setPosition(m_windowSize.x, m_playerSprite.getPosition().y);
    }
    else if (m_playerSprite.getPosition().x > m_windowSize.x)
    {
        m_playerSprite.setPosition(0, m_playerSprite.getPosition().y);
    }

    if (m_playerSprite.getPosition().y < 0)
    {
        m_playerSprite.setPosition(m_playerSprite.getPosition().x, m_windowSize.y);
    }
    else if (m_playerSprite.getPosition().y > m_windowSize.y)
    {
        m_playerSprite.setPosition(m_playerSprite.getPosition().x, 0);
    }
}
