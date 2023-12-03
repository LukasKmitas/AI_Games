#include "Tile.h"

Tile::Tile()
{
	m_isPlaced = false;
	m_tileShape = nullptr;
    m_shape = TileShape::Empty;
    m_color = TileColor::Empty;
}

Tile::~Tile()
{
}

void Tile::setShape(TileShape shape)
{
    m_shape = shape;
    createTileShape();
}

void Tile::setColor(TileColor color)
{
    m_color = color;
    createTileShape();
}

std::string Tile::getShapeAsString() const
{
    switch (m_shape)
    {
    case TileShape::Empty: return "Empty";
    case TileShape::Circle: return "Circle";
    case TileShape::Square: return "Square";
    case TileShape::Diamond: return "Diamond";
    case TileShape::Clover: return "Clover";
    case TileShape::EightStar: return "EightStar";
    case TileShape::FourthStar: return "FourthStar";
    default: return "Unknown";
    }
}

std::string Tile::getColorAsString() const
{
    switch (m_color) 
    {
    case TileColor::Empty: return "Empty";
    case TileColor::Red: return "Red";
    case TileColor::Orange: return "Orange";
    case TileColor::Yellow: return "Yellow";
    case TileColor::Green: return "Green";
    case TileColor::Blue: return "Blue";
    case TileColor::Purple: return "Purple";
    default: return "Unknown";
    }
}

void Tile::createTileShape()
{
    switch (m_shape)
    {
    case TileShape::Circle:
        m_tileShape = new sf::CircleShape(20);
        m_tileShape->setOrigin(20, 20);
        break;
    case TileShape::Square:
        m_tileShape = new sf::RectangleShape(sf::Vector2f(40, 40));
        m_tileShape->setOrigin(20, 20);
        break;
    case TileShape::Diamond:
        m_tileShape = new sf::ConvexShape(4);
        dynamic_cast<sf::ConvexShape*>(m_tileShape)->setPoint(0, sf::Vector2f(20, 0)); // Top
        dynamic_cast<sf::ConvexShape*>(m_tileShape)->setPoint(1, sf::Vector2f(40, 20)); // Right
        dynamic_cast<sf::ConvexShape*>(m_tileShape)->setPoint(2, sf::Vector2f(20, 40)); // Bottom
        dynamic_cast<sf::ConvexShape*>(m_tileShape)->setPoint(3, sf::Vector2f(0, 20)); // Left
        m_tileShape->setOrigin(20, 20);
        break;
    case TileShape::Clover:
        m_tileShape = new sf::ConvexShape(16);
        for (int i = 0; i < 16; ++i) 
        {
            float angle = i * 45 * 3.14159265 / 180;
            int radius = (i % 2 == 0) ? 20 : 10;
            dynamic_cast<sf::ConvexShape*>(m_tileShape)->setPoint(i, sf::Vector2f(25 + radius * std::cos(angle), 25 + radius * std::sin(angle)));
        }
        m_tileShape->setOrigin(25, 25);
        break;
    case TileShape::EightStar:
        m_tileShape = new sf::ConvexShape(16);
        for (int i = 0; i < 16; ++i) 
        {
            float angle = i * 22.5 * 3.14159265 / 180;
            int radius = (i % 2 == 0) ? 20 : 10;
            dynamic_cast<sf::ConvexShape*>(m_tileShape)->setPoint(i, sf::Vector2f(25 + radius * std::cos(angle), 25 + radius * std::sin(angle)));
        }
        m_tileShape->setOrigin(25, 25);
        break;
    case TileShape::FourthStar:
        m_tileShape = new sf::ConvexShape(8);
        for (int i = 0; i < 8; ++i) 
        {
            float angle = i * 45 * 3.14159265 / 180;
            int radius = (i % 2 == 0) ? 20 : 10;
            dynamic_cast<sf::ConvexShape*>(m_tileShape)->setPoint(i, sf::Vector2f(25 + radius * std::cos(angle), 25 + radius * std::sin(angle)));
        }
        dynamic_cast<sf::ConvexShape*>(m_tileShape)->setRotation(45);
        m_tileShape->setOrigin(25, 25);
        break;
    default:
        m_tileShape = nullptr;
        break;
    }


    if (m_tileShape) 
    {
        switch (m_color)
        {
        case TileColor::Red:
            m_tileShape->setFillColor(sf::Color::Red);
            break;
        case TileColor::Orange:
            m_tileShape->setFillColor(sf::Color(255, 165, 0));
            break;
        case TileColor::Yellow:
            m_tileShape->setFillColor(sf::Color::Yellow);
            break;
        case TileColor::Green:
            m_tileShape->setFillColor(sf::Color(10,180,0));
            break;
        case TileColor::Blue:
            m_tileShape->setFillColor(sf::Color::Blue);
            break;
        case TileColor::Purple:
            m_tileShape->setFillColor(sf::Color::Magenta);
            break;
        default:
            break;
        }
    }
}

sf::Shape* Tile::getTileShape() const 
{
    return m_tileShape;
}

void Tile::setPosition(const sf::Vector2i& newPosition)
{
    position = newPosition;
}
