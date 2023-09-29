#include "Player.h"
#include <iostream>

Player::Player()
{
	setupPlayer();
    setupConeOfVision();
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

    sf::Vector2f direction = sf::Vector2f(std::cos(toRadians(m_playerSprite.getRotation() - 90)),
        std::sin(toRadians(m_playerSprite.getRotation() - 90)));

    m_directionLine[0].position = m_playerSprite.getPosition();
    m_directionLine[1].position = m_playerSprite.getPosition() - direction * 200.0f;

    m_coneRotation = m_coneOfVision.getRotation();
    m_coneOfVision.rotate(m_coneRotation);
    coneOfVision();
}

void Player::draw(sf::RenderWindow& m_window)
{
    m_window.draw(m_coneOfVision);
    m_window.draw(m_directionLine);
	m_window.draw(m_playerSprite);
}

sf::Vector2f Player::getPosition() const
{
	return m_playerSprite.getPosition();
}

sf::Vector2f Player::getVelocity() const
{
    return m_velocity;
}

/// <summary>
/// Sets up the player sprite/properties
/// </summary>
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

    m_directionLine[0].position = m_playerSprite.getPosition();
    m_directionLine[1].position = m_playerSprite.getPosition();
    m_directionLine[1].position.x += 100.0f;
    m_directionLine[0].color = sf::Color::Black;
    m_directionLine[1].color = sf::Color::Black;
}

/// <summary>
/// Sets up the vision of cone 
/// </summary>
void Player::setupConeOfVision()
{
    m_coneOfVision.setPointCount(3);
    m_coneOfVision.setFillColor(sf::Color(0, 0, 0, 100));
    m_coneOfVision.setOutlineThickness(5);
}

/// <summary>
/// Makes the player move like a car
/// </summary>
void Player::movement()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_playerSprite.rotate(-m_rotationSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_playerSprite.rotate(m_rotationSpeed);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        sf::Vector2f direction = normalize(sf::Vector2f(std::cos(toRadians(m_playerSprite.getRotation() - 90)),
            std::sin(toRadians(m_playerSprite.getRotation() - 90))));
        m_velocity -= direction * m_acceleration;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        sf::Vector2f direction = normalize(sf::Vector2f(std::cos(toRadians(m_playerSprite.getRotation() - 90)),
            std::sin(toRadians(m_playerSprite.getRotation() - 90))));
        m_velocity += direction * m_acceleration;
    }

    // For deceleration
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (length(m_velocity) > 0)
        {
            m_velocity -= normalize(m_velocity) * m_deceleration;
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

void Player::coneOfVision()
{
    sf::Vector2f playerPos = m_playerSprite.getPosition();
    m_coneOfVision.setPosition(playerPos);

    m_coneOfVision.setRotation(m_playerSprite.getRotation() + 90);

    sf::Vector2f p1(0.0f, 0.0f); // Origin
    sf::Vector2f p2(200.0f, -50.0f); //width
    sf::Vector2f p3(200.0f, 50.0f); //width

    m_coneOfVision.setPoint(0, p1);
    m_coneOfVision.setPoint(1, p2);
    m_coneOfVision.setPoint(2, p3);
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

float Player::toRadians(float degrees)
{
    return degrees * 3.14159265359f / 180.0f;
}