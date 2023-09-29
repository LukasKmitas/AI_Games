#include "EnemyBase.h"
#include <iostream>

void EnemyBase::update(sf::Time t_deltaTime)
{
    wrapAround();
    float deltaTimeSec = t_deltaTime.asSeconds();
    m_enemySprite.move(m_velocity * deltaTimeSec);

    sf::Vector2f direction = sf::Vector2f(std::cos(toRadians(m_enemySprite.getRotation() - 90)),
        std::sin(toRadians(m_enemySprite.getRotation() - 90)));

    m_directionLine[0].position = m_enemySprite.getPosition();
    m_directionLine[1].position = m_enemySprite.getPosition() - direction * 200.0f;

    m_coneRotation = m_coneOfVision.getRotation();
    m_coneOfVision.rotate(m_coneRotation);
    coneOfVision();

    m_enemyTypeText.setPosition(m_enemySprite.getPosition().x + 50, m_enemySprite.getPosition().y - 100);
}

void EnemyBase::draw(sf::RenderWindow& m_window)
{
    m_window.draw(m_coneOfVision);
    m_window.draw(m_directionLine);
    m_window.draw(m_enemySprite);
    m_window.draw(m_enemyTypeText);
}

void EnemyBase::setupEnemy()
{
    if (!m_enemyTexture.loadFromFile("Assets\\Images\\Enemy_Pirate.png"))
    {
        std::cout << "problem loading image" << std::endl;
    }
    m_enemyTexture.setSmooth(true);
    m_enemySprite.setTexture(m_enemyTexture);
    m_enemySprite.setPosition(100.0f, 100.0f);
    m_enemySprite.setOrigin(m_enemySprite.getTextureRect().width / 2, m_enemySprite.getTextureRect().height / 2);
    m_enemySprite.setScale(0.3, 0.3);
}

void EnemyBase::wrapAround()
{
    if (m_enemySprite.getPosition().x < 0)
    {
        m_enemySprite.setPosition(ScreenSize::s_width, m_enemySprite.getPosition().y);
    }
    else if (m_enemySprite.getPosition().x > ScreenSize::s_width)
    {
        m_enemySprite.setPosition(0, m_enemySprite.getPosition().y);
    }

    if (m_enemySprite.getPosition().y < 0)
    {
        m_enemySprite.setPosition(m_enemySprite.getPosition().x, ScreenSize::s_height);
    }
    else if (m_enemySprite.getPosition().y > ScreenSize::s_height)
    {
        m_enemySprite.setPosition(m_enemySprite.getPosition().x, 0);
    }
}

void EnemyBase::setupConeOfVision()
{
    m_coneOfVision.setPointCount(3);
    m_coneOfVision.setFillColor(sf::Color(0, 0, 0, 100));
    m_coneOfVision.setOutlineThickness(5);
}

void EnemyBase::coneOfVision()
{
    sf::Vector2f playerPos = m_enemySprite.getPosition();
    m_coneOfVision.setPosition(playerPos);

    m_coneOfVision.setRotation(m_enemySprite.getRotation() + 90);

    sf::Vector2f p1(0.0f, 0.0f); // Origin
    sf::Vector2f p2(150.0f, -50.0f); //width
    sf::Vector2f p3(150.0f, 50.0f); //width

    m_coneOfVision.setPoint(0, p1);
    m_coneOfVision.setPoint(1, p2);
    m_coneOfVision.setPoint(2, p3);
}

void EnemyBase::setupFontAndText()
{
    if (!m_ArialBlackfont.loadFromFile("Assets\\Fonts\\ariblk.ttf"))
    {
        std::cout << "problem loading font" << std::endl;
    }
    m_enemyTypeText.setFont(m_ArialBlackfont);
    m_enemyTypeText.setString("TEXT");
    m_enemyTypeText.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
    m_enemyTypeText.setCharacterSize(20U);
    m_enemyTypeText.setFillColor(sf::Color::Black);
}

float EnemyBase::getNewOrientation(float m_currentOrientation, sf::Vector2f m_velocity)
{
    if (std::abs(m_velocity.x) > 0 || std::abs(m_velocity.y) > 0)
    {
        return std::atan2(m_velocity.y, m_velocity.x);
    }
    else
    {
        return m_currentOrientation;
    }
}

sf::Vector2f EnemyBase::normalize(sf::Vector2f vector)
{
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
    if (length != 0)
    {
        vector.x /= length;
        vector.y /= length;
    }
    return vector;
}

float EnemyBase::length(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float EnemyBase::toRadians(float degrees)
{
    return degrees * 3.14159265359f / 180.0f;
}
