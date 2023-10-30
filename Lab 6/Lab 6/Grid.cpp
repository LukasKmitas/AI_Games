#include "Grid.h"

Grid::Grid()
    : m_displayText(true),
    m_startTile(-1, -1),
    m_goalTile(-1, -1)
{
    m_tiles.resize(Global::GRID_HEIGHT, std::vector<Tile>(Global::GRID_WIDTH));

    m_currentStartTile = sf::Vector2i(-1, -1);
    m_currentGoalTile = sf::Vector2i(-1, -1);
    m_currentObstacleTile = sf::Vector2i(-1, -1);

    setupFontAndText();

    for (int row = 0; row < Global::GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < Global::GRID_WIDTH; ++col)
        {
            m_tiles[row][col].m_tile.setSize(sf::Vector2f(Global::TILE_SIZE, Global::TILE_SIZE));
            m_tiles[row][col].m_tile.setPosition(sf::Vector2f(col * Global::TILE_SIZE, row * Global::TILE_SIZE));
            m_tiles[row][col].m_tile.setFillColor(sf::Color::Black);
            m_tiles[row][col].m_tile.setOutlineColor(sf::Color::White);
            m_tiles[row][col].m_tile.setOutlineThickness(1);
            m_tiles[row][col].isTraversable = true;
            m_tiles[row][col].m_cost = 1;
            m_tiles[row][col].m_integrationF = 0;
            
            m_tiles[row][col].m_number = tileNumber;
            tileNumber++;
        }
    }
    setCostField();
    calculateVectorField();
}

void Grid::render(sf::RenderWindow& window)
{
    for (int row = 0; row < Global::GRID_HEIGHT; row++)
    {
        for (int col = 0; col < Global::GRID_WIDTH; col++)
        {
            m_tiles[row][col].m_tile.setPosition(sf::Vector2f(col * Global::TILE_SIZE, row * Global::TILE_SIZE));

            window.draw(m_tiles[row][col].m_tile);

            if (m_displayText)
            {
                m_tileNumberText.setString(std::to_string(m_tiles[row][col].m_number));
                m_tileNumberText.setPosition(m_tiles[row][col].m_tile.getPosition());
                window.draw(m_tileNumberText);
            }

            if (m_tiles[row][col].isTraversable)
            {
                // Draw arrows representing the vector field
                sf::Vector2f tileCenter = m_tiles[row][col].m_tile.getPosition() + sf::Vector2f(Global::TILE_SIZE / 2, Global::TILE_SIZE / 2);
                sf::Vector2f vector = m_tiles[row][col].m_flowField;

                sf::Color vectorColor = m_tiles[row][col].m_vectorColor;
                sf::Vector2f arrowEnd = tileCenter + vector * (Global::TILE_SIZE / 2.0f * scalingFactor);

                float arrowThickness = 1.0f;
                sf::Vector2f arrowDirection = arrowEnd - tileCenter;
                float arrowLength = std::sqrt(arrowDirection.x * arrowDirection.x + arrowDirection.y * arrowDirection.y);

                // Create a rectangle for the arrow
                sf::RectangleShape arrowRect(sf::Vector2f(arrowLength, arrowThickness));
                arrowRect.setPosition(tileCenter);
                arrowRect.setRotation(std::atan2(arrowDirection.y, arrowDirection.x) * 180.0f / static_cast<float>(PI));
                arrowRect.setFillColor(vectorColor);

                window.draw(arrowRect);
            }
        }
    }
}

Tile& Grid::getTile(int row, int col)
{
    return m_tiles[row][col];
}

void Grid::setTileCost(int row, int col, int cost)
{
    m_tiles[row][col].m_cost = cost;
}

void Grid::setTileTraversable(int row, int col, bool traversable)
{
    m_tiles[row][col].isTraversable = traversable;
}

void Grid::setupFontAndText()
{
    if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
    {
        std::cout << "problem loading arial black font" << std::endl;
    }
    m_tileNumberText.setFont(m_ArialBlackfont);
    m_tileNumberText.setStyle(sf::Text::Italic);
    m_tileNumberText.setCharacterSize(5U);
    m_tileNumberText.setFillColor(sf::Color::White);
}

void Grid::toggleTextDisplay()
{
    m_displayText = !m_displayText;
}

void Grid::setStartTile(const sf::Vector2i& startTile)
{
    if (m_currentStartTile != startTile)
    {
        if (m_currentStartTile != sf::Vector2i(-1, -1))
        {
            m_tiles[m_currentStartTile.y][m_currentStartTile.x].m_tile.setFillColor(sf::Color::Black);
        }

        m_currentStartTile = startTile;
        m_startTile = startTile;
        m_tiles[startTile.y][startTile.x].m_tile.setFillColor(sf::Color::Green);
        calculateVectorField();
    }
}

void Grid::setGoalTile(const sf::Vector2i& goalTile)
{
    if (m_currentGoalTile != goalTile)
    {
        if (m_currentGoalTile != sf::Vector2i(-1, -1))
        {
            m_tiles[m_currentGoalTile.y][m_currentGoalTile.x].m_tile.setFillColor(sf::Color::Black);
        }
        m_currentGoalTile = goalTile;
        m_goalTile = goalTile;
        m_tiles[goalTile.y][goalTile.x].m_tile.setFillColor(sf::Color::Red);
        calculateVectorField();
    }
}

void Grid::setObstacleTile(const sf::Vector2i& obstacleTile)
{
    if (m_currentObstacleTile == obstacleTile) 
    {
        m_tiles[obstacleTile.y][obstacleTile.x].isTraversable = true;
        m_tiles[obstacleTile.y][obstacleTile.x].m_tile.setFillColor(sf::Color::Black);
        m_tiles[obstacleTile.y][obstacleTile.x].m_cost = 1;
        m_currentObstacleTile = sf::Vector2i(-1, -1);
    }
    else 
    {
        m_currentObstacleTile = obstacleTile;
        m_tiles[obstacleTile.y][obstacleTile.x].isTraversable = false;
        m_tiles[obstacleTile.y][obstacleTile.x].m_tile.setFillColor(sf::Color::Blue);
        m_tiles[obstacleTile.y][obstacleTile.x].m_cost = 100;
    }
    calculateVectorField();
}

void Grid::setCostField()
{
    for (int row = 0; row < Global::GRID_HEIGHT; ++row) 
    {
        for (int col = 0; col < Global::GRID_WIDTH; ++col) 
        {
            if (m_tiles[row][col].isTraversable) 
            {
                m_tiles[row][col].m_cost = 1;
            }
            else 
            {
                m_tiles[row][col].m_cost = 100;
            }
        }
    }
}

void Grid::calculateVectorField() 
{
    for (int row = 0; row < Global::GRID_HEIGHT; ++row) 
    {
        for (int col = 0; col < Global::GRID_WIDTH; ++col) 
        {
            if (m_tiles[row][col].isTraversable) 
            {
                // Find the neighboring tile with the lowest cost
                int minCost = m_tiles[row][col].m_cost;
                sf::Vector2f vectorToLowestCostTile(0, 0);

                for (int i = -1; i <= 1; ++i) 
                {
                    for (int j = -1; j <= 1; ++j) 
                    {
                        int newRow = row + i;
                        int newCol = col + j;

                        if (newRow >= 0 && newRow < Global::GRID_HEIGHT && newCol >= 0 && newCol < Global::GRID_WIDTH)
                        {
                            int cost = m_tiles[newRow][newCol].m_cost;
                            if (cost < minCost)
                            {
                                minCost = cost;
                                vectorToLowestCostTile = sf::Vector2f(newCol - col, newRow - row);
                            }
                        }
                    }
                }

                float length = std::sqrt(vectorToLowestCostTile.x * vectorToLowestCostTile.x + vectorToLowestCostTile.y * vectorToLowestCostTile.y);
                if (length != 0) 
                {
                    vectorToLowestCostTile.x /= length;
                    vectorToLowestCostTile.y /= length;
                }

                // Set the vector field for this tile
                m_tiles[row][col].m_flowField = vectorToLowestCostTile;

                // Calculate color based on vector direction
                sf::Vector2f normalizedVector = vectorToLowestCostTile;
                float vectorLength = std::sqrt(normalizedVector.x * normalizedVector.x + normalizedVector.y * normalizedVector.y);

                if (vectorLength > 0) 
                {
                    normalizedVector.x /= vectorLength;
                    normalizedVector.y /= vectorLength;
                }

                sf::Uint8 r = static_cast<sf::Uint8>((normalizedVector.x + 1.0) * 127);
                sf::Uint8 g = static_cast<sf::Uint8>((normalizedVector.y + 1.0) * 127);
                sf::Uint8 b = 255;
                sf::Uint8 a = 200;

                sf::Color vectorColor(r, g, b, a);
                m_tiles[row][col].m_vectorColor = vectorColor;
            }
        }
    }
}
