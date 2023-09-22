#pragma once

#include <SFML/Graphics.hpp>
#include "ScreenSize.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void update(sf::Time t_deltaTime);
	void draw(sf::RenderWindow& m_window);

private:

	void setupEnemy();
	void wrapAround();

	sf::Texture m_enemyTexture;
	sf::Sprite m_enemySprite;

};

