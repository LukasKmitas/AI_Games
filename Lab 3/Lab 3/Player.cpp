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
	if (!m_playerTexture.loadFromFile("Assets\\Images\\hai.png"))
	{
		std::cout << "problem loading image" << std::endl;
	}
    m_playerTexture.setSmooth(true);
	m_playerSprite.setTexture(m_playerTexture);
	m_playerSprite.setPosition(600.0f, 700.0f);
    m_playerSprite.setTextureRect(sf::IntRect(0, 0, 148, 141));
	m_playerSprite.setOrigin(m_playerSprite.getTextureRect().width / 2, m_playerSprite.getTextureRect().height / 2);
	m_playerSprite.setScale(0.5, 0.5);
    m_playerSprite.setRotation(180);
}

void Player::movement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_velocity.x -= m_acceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_velocity.x += m_acceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_velocity.y -= m_acceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_velocity.y += m_acceleration;
    }

    // For deceleration
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (m_velocity.x > 0)
        {
            m_velocity.x -= m_deceleration;
            if (m_velocity.x < 0)
            {
                m_velocity.x = 0;
            }
        }
        else if (m_velocity.x < 0)
        {
            m_velocity.x += m_deceleration;
            if (m_velocity.x > 0)
            {
                m_velocity.x = 0;
            }
        }
    }

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (m_velocity.y > 0)
        {
            m_velocity.y -= m_deceleration;
            if (m_velocity.y < 0)
            {
                m_velocity.y = 0;
            }
        }
        else if (m_velocity.y < 0)
        {
            m_velocity.y += m_deceleration;
            if (m_velocity.y > 0)
            {
                m_velocity.y = 0;
            }
        }
    }
}

void Player::wrapAround()
{
    if (m_playerSprite.getPosition().x < 0)
    {
        m_playerSprite.setPosition(ScreenSize::s_width, m_playerSprite.getPosition().y);
    }
    else if (m_playerSprite.getPosition().x > ScreenSize::s_width)
    {
        m_playerSprite.setPosition(0, m_playerSprite.getPosition().y);
    }

    if (m_playerSprite.getPosition().y < 0)
    {
        m_playerSprite.setPosition(m_playerSprite.getPosition().x, ScreenSize::s_height);
    }
    else if (m_playerSprite.getPosition().y > ScreenSize::s_height)
    {
        m_playerSprite.setPosition(m_playerSprite.getPosition().x, 0);
    }
}

sf::Vector2f Player::normalize(sf::Vector2f vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
    {
        vector.x /= length;
        vector.y /= length;
    }
    return vector;
}

float Player::length(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}
