#include "Grid.h"

Grid::Grid()
    : 
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
    m_displayText = false;
    m_displayCost = false;
    m_displayIntegrationField = false;
    m_displayPath = false;
}

void Grid::render(sf::RenderWindow& window)
{
    for (int row = 0; row < Global::GRID_HEIGHT; row++)
    {
        for (int col = 0; col < Global::GRID_WIDTH; col++)
        {
            m_tiles[row][col].m_tile.setPosition(sf::Vector2f(col * Global::TILE_SIZE, row * Global::TILE_SIZE));
            if (sf::Vector2i(col, row) != m_startTile && sf::Vector2i(col, row) != m_goalTile && m_tiles[row][col].isTraversable)
            {
                int cost = m_tiles[row][col].m_cost;
                int maxCost = 80;
                int minCost = 1;
                float colorIntensity = static_cast<float>(cost - minCost) / (maxCost - minCost);
                sf::Color tileColor(0, 0, static_cast<sf::Uint8>(255 * (1.0f - colorIntensity)), 200);
                m_tiles[row][col].m_tile.setFillColor(tileColor);
            }

            window.draw(m_tiles[row][col].m_tile);

            if (m_displayText)
            {
                m_tileNumberText.setString(std::to_string(m_tiles[row][col].m_number));
                m_tileNumberText.setPosition(m_tiles[row][col].m_tile.getPosition());
                window.draw(m_tileNumberText);
            }

            if (m_displayCost)
            {
                m_tileNumberText.setString(std::to_string(m_tiles[row][col].m_cost));
                m_tileNumberText.setPosition(m_tiles[row][col].m_tile.getPosition() + sf::Vector2f(5.0f, 5.0f)); // Adjust the position for better visibility.
                window.draw(m_tileNumberText);
            }

            if (m_displayIntegrationField)
            {
                m_tileNumberText.setString(std::to_string(m_tiles[row][col].m_integrationF));
                m_tileNumberText.setPosition(m_tiles[row][col].m_tile.getPosition() + sf::Vector2f(5.0f, 5.0f)); // Adjust the position for better visibility.
                window.draw(m_tileNumberText);
            }

            if (m_displayPath) 
            {
                for (const sf::Vector2i& pathTile : m_path) 
                {
                    int row = pathTile.y;
                    int col = pathTile.x;
                    if (pathTile != m_startTile && pathTile != m_goalTile) 
                    {
                        m_tiles[row][col].m_tile.setFillColor(sf::Color(0, 128, 0, 200));
                    }
                    window.draw(m_tiles[row][col].m_tile);
                }
            }


            if (m_tiles[row][col].isTraversable)
            {
                // Draw arrows representing the vector field
                sf::Vector2f tileCenter = m_tiles[row][col].m_tile.getPosition() + sf::Vector2f(Global::TILE_SIZE / 2, Global::TILE_SIZE / 2);
                sf::Vector2f vector = m_tiles[row][col].m_flowField;

                //std::cout << "Vector at (" << row << ", " << col << "): (" << vector.x << ", " << vector.y << ")" << std::endl;

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
    m_tileNumberText.setCharacterSize(7U);
    m_tileNumberText.setFillColor(sf::Color::White);
}

void Grid::toggleTextDisplay()
{
    m_displayText = !m_displayText;
}

void Grid::toggleCostDisplay()
{
    m_displayCost = !m_displayCost;
}

void Grid::toggleIntegrationFieldDisplay()
{
    m_displayIntegrationField = !m_displayIntegrationField;
}

void Grid::togglePathDisplay()
{
    m_displayPath = !m_displayPath;
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

        if (m_currentGoalTile != sf::Vector2i(-1, -1))
        {
            calculateCostField();
            calculateIntegrationField();
            calculateVectorField();
        }
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

        if (m_currentStartTile != sf::Vector2i(-1, -1))
        {
            calculateCostField();
            calculateIntegrationField();
            calculateVectorField();
        }
    }
}

void Grid::setObstacleTile(const sf::Vector2i& obstacleTile)
{
    if (m_currentObstacleTile == obstacleTile) 
    {
        m_tiles[obstacleTile.y][obstacleTile.x].isTraversable = true;
        m_tiles[obstacleTile.y][obstacleTile.x].m_cost = 1;
        m_currentObstacleTile = sf::Vector2i(-1, -1);
    }
    else 
    {
        m_currentObstacleTile = obstacleTile;
        m_tiles[obstacleTile.y][obstacleTile.x].isTraversable = false;
        m_tiles[obstacleTile.y][obstacleTile.x].m_tile.setFillColor(sf::Color::Black);
        m_tiles[obstacleTile.y][obstacleTile.x].m_cost = 100;
    }
    if (m_currentStartTile != sf::Vector2i(-1, -1) && m_currentGoalTile != sf::Vector2i(-1, -1))
    {
        calculateCostField();
        calculateIntegrationField();
        calculateVectorField();
    }
}

void Grid::calculateCostField()
{
    for (int row = 0; row < Global::GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < Global::GRID_WIDTH; ++col)
        {
            if (m_tiles[row][col].isTraversable)
            {
                m_tiles[row][col].m_cost = std::numeric_limits<int>::max();
            }
        }
    }

    sf::Vector2i goal = m_goalTile;
    m_tiles[goal.y][goal.x].m_cost = 0;

    std::queue<sf::Vector2i> queue;
    queue.push(goal);

    while (!queue.empty())
    {
        sf::Vector2i currentTile = queue.front();
        queue.pop();

        int currentCost = m_tiles[currentTile.y][currentTile.x].m_cost;

        // Explore neighbors
        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j)
            {
                int newRow = currentTile.y + i;
                int newCol = currentTile.x + j;

                if (newRow >= 0 && newRow < Global::GRID_HEIGHT && newCol >= 0 && newCol < Global::GRID_WIDTH)
                {
                    if (m_tiles[newRow][newCol].isTraversable)
                    {
                        int newCost = currentCost + 1;

                        // Update cost
                        if (newCost < m_tiles[newRow][newCol].m_cost)
                        {
                            m_tiles[newRow][newCol].m_cost = newCost;
                            queue.push(sf::Vector2i(newCol, newRow));
                        }
                    }
                }
            }
        }
    }
}

void Grid::calculateIntegrationField()
{
    for (int row = 0; row < Global::GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < Global::GRID_WIDTH; ++col)
        {
            m_tiles[row][col].m_integrationF = std::numeric_limits<int>::max();
        }
    }

    sf::Vector2i goal = m_goalTile;
    m_tiles[goal.y][goal.x].m_integrationF = 0;

    std::queue<sf::Vector2i> queue;
    queue.push(goal);

    while (!queue.empty())
    {
        sf::Vector2i currentTile = queue.front();
        queue.pop();

        int currentIntegrationField = m_tiles[currentTile.y][currentTile.x].m_integrationF;

        // Explore neighbors
        for (int i = -1; i <= 1; ++i)
        {
            for (int j = -1; j <= 1; ++j)
            {
                int newRow = currentTile.y + i;
                int newCol = currentTile.x + j;

                if (newRow >= 0 && newRow < Global::GRID_HEIGHT && newCol >= 0 && newCol < Global::GRID_WIDTH)
                {
                    if (m_tiles[newRow][newCol].isTraversable)
                    {
                        int newIntegrationField = currentIntegrationField + m_tiles[newRow][newCol].m_cost;

                        // Update integration field
                        if (newIntegrationField < m_tiles[newRow][newCol].m_integrationF)
                        {
                            m_tiles[newRow][newCol].m_integrationF = newIntegrationField;
                            queue.push(sf::Vector2i(newCol, newRow));
                        }
                    }
                }
            }
        }
    }

    // Finding the shortest path to end goal
    m_path.clear();
    sf::Vector2i currentTile = m_startTile;

    while (currentTile != m_goalTile) 
    {
        m_path.push_back(currentTile);

        int currentIntegrationField = m_tiles[currentTile.y][currentTile.x].m_integrationF;
        sf::Vector2i bestNeighbor(-1, -1);

        for (int i = -1; i <= 1; ++i) 
        {
            for (int j = -1; j <= 1; ++j)
            {
                int newRow = currentTile.y + i;
                int newCol = currentTile.x + j;

                if (newRow >= 0 && newRow < Global::GRID_HEIGHT && newCol >= 0 && newCol < Global::GRID_WIDTH) {
                    if (m_tiles[newRow][newCol].isTraversable && m_tiles[newRow][newCol].m_integrationF < currentIntegrationField) {
                        currentIntegrationField = m_tiles[newRow][newCol].m_integrationF;
                        bestNeighbor = sf::Vector2i(newCol, newRow);
                    }
                }
            }
        }
        currentTile = bestNeighbor;
    }
    m_path.push_back(m_goalTile);
}

void Grid::calculateVectorField()
{
    for (int row = 0; row < Global::GRID_HEIGHT; ++row)
    {
        for (int col = 0; col < Global::GRID_WIDTH; ++col)
        {
            if (m_tiles[row][col].isTraversable)
            {
                int minIntegrationField = m_tiles[row][col].m_integrationF;
                sf::Vector2i bestNeighbor(-1, -1);

                for (int i = -1; i <= 1; ++i)
                {
                    for (int j = -1; j <= 1; ++j)
                    {
                        int newRow = row + i;
                        int newCol = col + j;

                        if (newRow >= 0 && newRow < Global::GRID_HEIGHT && newCol >= 0 && newCol < Global::GRID_WIDTH)
                        {
                            if (m_tiles[newRow][newCol].isTraversable && m_tiles[newRow][newCol].m_integrationF < minIntegrationField)
                            {
                                minIntegrationField = m_tiles[newRow][newCol].m_integrationF;
                                bestNeighbor = sf::Vector2i(newCol, newRow);
                            }
                        }
                    }
                }

                // Calculate the vector from this tile to the best neighbor
                sf::Vector2f vectorToBestNeighbor = sf::Vector2f(bestNeighbor.x - col, bestNeighbor.y - row);

                float length = std::sqrt(vectorToBestNeighbor.x * vectorToBestNeighbor.x + vectorToBestNeighbor.y * vectorToBestNeighbor.y);
                if (length != 0)
                {
                    vectorToBestNeighbor.x /= length;
                    vectorToBestNeighbor.y /= length;
                }

                m_tiles[row][col].m_flowField = vectorToBestNeighbor;

                // Calculate color based on vector direction
                sf::Vector2f normalizedVector = vectorToBestNeighbor;
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

