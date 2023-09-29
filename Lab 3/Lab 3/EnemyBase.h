#pragma once
#include "SFML/Graphics.hpp"
#include "ScreenSize.h"

struct SteeringOutput 
{
	sf::Vector2f linear;
	float angular;
};

class EnemyBase
{
public:

	virtual ~EnemyBase() = default;

	virtual void update(sf::Time t_deltaTime) = 0;
	virtual void draw(sf::RenderWindow& m_window) = 0;


protected:

	void setupEnemy();
	void wrapAround();

	void setupConeOfVision();
	void coneOfVision();

	void setupFontAndText();

	float getNewOrientation(float m_currentOrientation, sf::Vector2f m_velocity);
	sf::Vector2f normalize(sf::Vector2f vector);
	float length(sf::Vector2f vector);
	float toRadians(float degrees);

	sf::Texture m_enemyTexture;
	sf::Sprite m_enemySprite;

	sf::Font m_ArialBlackfont;
	sf::Text m_enemyTypeText;

	sf::ConvexShape m_coneOfVision;
	sf::VertexArray m_directionLine{ sf::Lines, 2 };

	sf::Vector2f m_velocity;

	float m_orientation = 0;
	float m_coneRotation = 0.0f;
	float m_maxAcceleration = 100.0f;

};

