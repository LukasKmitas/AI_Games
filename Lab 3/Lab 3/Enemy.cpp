#include "Enemy.h"
#include <iostream>

Enemy::Enemy()
{
	setupEnemy();
}

Enemy::~Enemy()
{
}

void Enemy::update(sf::Time t_deltaTime)
{

}

void Enemy::draw(sf::RenderWindow& m_window)
{
	m_window.draw(m_enemySprite);
}

void Enemy::setupEnemy()
{
    if (!m_enemyTexture.loadFromFile("Assets\\Images\\Enemy_Pirate.png"))
    {
        std::cout << "problem loading image" << std::endl;
    }
    m_enemyTexture.setSmooth(true);
    m_enemySprite.setTexture(m_enemyTexture);
    m_enemySprite.setPosition(600.0f, 100.0f);
    m_enemySprite.setOrigin(m_enemySprite.getTextureRect().width / 2, m_enemySprite.getTextureRect().height / 2);
    m_enemySprite.setScale(0.3, 0.3);
}

void Enemy::wrapAround()
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
