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

/// <summary>
/// To draw the grid and everything needed for it
/// </summary>
/// <param name="window"> window </param>
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
                m_tileNumberText.setPosition(m_tiles[row][col].m_tile.getPosition() + sf::Vector2f(5.0f, 5.0f));
                window.draw(m_tileNumberText);
            }

            if (m_displayIntegrationField)
            {
                m_tileNumberText.setString(std::to_string(m_tiles[row][col].m_integrationF));
                m_tileNumberText.setPosition(m_tiles[row][col].m_tile.getPosition() + sf::Vector2f(5.0f, 5.0f));
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

/// <summary>
/// To get that Tile
/// </summary>
/// <param name="row"> which Row </param>
/// <param name="col"> which Col</param>
/// <returns> returns that Tile </returns>
Tile& Grid::getTile(int row, int col)
{
    return m_tiles[row][col];
}

/// <summary>
/// Sets that tiles cost
/// </summary>
/// <param name="row"> tiles Row </param>
/// <param name="col"> tiles Col </param>
/// <param name="cost"> cost int </param>
void Grid::setTileCost(int row, int col, int cost)
{
    m_tiles[row][col].m_cost = cost;
}

/// <summary>
/// Sets if that tile is Traversable or not (Obstacle)
/// </summary>
/// <param name="row"> tiles Row </param>
/// <param name="col"> tiles Col </param>
/// <param name="traversable"> true or false </param>
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
    m_tileNumberText.setCharacterSize(12U);
    //m_tileNumberText.setCharacterSize(8U);
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

/// <summary>
/// Sets the start tile
/// </summary>
/// <param name="startTile"> beginning Tile </param>
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

/// <summary>
/// Sets up the End tile (Goal)
/// </summary>
/// <param name="goalTile"> ending tile </param>
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

/// <summary>
/// Sets up the obstacle tile
/// </summary>
/// <param name="obstacleTile"> true or false on that tile </param>
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

/// <summary>
/// A cost field (sometimes called a heatmap)
/// Store the path distance (not Euclidian) from the goal to every tile on the map
/// First, the algorithm begins at the goal, and marks it with a path distance of 0.
/// Then, it gets each tile's unmarked neighbours, and marks them with the previous tile's path distance + 1.
/// This continues until the entire reachable map has been marked.
/// </summary>
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

/// <summary>
/// 2. Generate the integration field
/// First, begin at the goal, and set it’s integration field to 0.#
/// Then, for each tile's unprocessed neighbours, 
/// their integration field is calculated by adding the direct distance to the goal tile to it’s cost field.
/// This continues until the entire reachable map has been marked.
/// </summary>
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
                        // Calculate the direct distance to the goal
                        int dx = std::abs(newCol - goal.x);
                        int dy = std::abs(newRow - goal.y);
                        int directDistance = dx + dy;

                        int newIntegrationField = currentIntegrationField + m_tiles[newRow][newCol].m_cost + directDistance;

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

                if (newRow >= 0 && newRow < Global::GRID_HEIGHT && newCol >= 0 && newCol < Global::GRID_WIDTH) 
                {
                    if (m_tiles[newRow][newCol].isTraversable && m_tiles[newRow][newCol].m_integrationF < currentIntegrationField) 
                    {
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

/// <summary>
/// Flow field (sometimes called a vector field)
/// The vector field simply stores a vector that points down the gradient
/// of the distance function (towards the goal) at every tile
/// Vectors point from the center of the tile along the shortest path to the goal(in red)
/// This vector field is generated one tile at a time by looking at the integration fields
/// of its neighbouring cells and identifying the lowest value.
/// </summary>
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

                // Assigning flowField
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

/// <summary>
/// Gets Path
/// </summary>
/// <returns> path </returns>
std::vector<sf::Vector2i> Grid::getPath() const
{
    return m_path;
}

/// <summary>
/// Gets the position of the tile
/// </summary>
/// <param name="tile"></param>
/// <returns></returns>
sf::Vector2f Grid::getPositionInTile(const sf::Vector2i& tile) const
{
    float x = static_cast<float>(tile.x) * Global::TILE_SIZE;
    float y = static_cast<float>(tile.y) * Global::TILE_SIZE;
    return sf::Vector2f(x , y);
}
