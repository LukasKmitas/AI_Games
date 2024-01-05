#include "Board.h"

Board::Board()
{
    setupFontAndText();
    setupUI();
	initializeGrid();
    fillBag();
    randomTilesInHolder();
}

Board::~Board()
{
}

void Board::render(sf::RenderWindow& m_window)
{
    for (const auto& row : gridRectangles)
    {
        for (const auto& rect : row) 
        {
            m_window.draw(rect);
        }
    }
    
    m_window.draw(m_bottomUI);
    m_window.draw(m_seperationLineUI);
    m_window.draw(m_boxBagForTextUI);
    m_window.draw(m_tileHolder[0]);
    m_window.draw(m_tileHolder[1]);

    sf::Vector2f boxBagPosition = m_boxBagForTextUI.getPosition();
    std::string numTiles = std::to_string(tileBag.size());
    m_bagText.setString(numTiles);
    m_bagText.setPosition(boxBagPosition.x - m_bagText.getLocalBounds().width / 2.0f,
        boxBagPosition.y + m_boxBagForTextUI.getSize().y / 2.0f - m_bagText.getCharacterSize());
    m_window.draw(m_bagText);

    for (const auto& tile : tilesOnBoard) 
    {
        sf::Shape* tileShape = tile.getTileShape();
        if (tileShape) 
        {
            m_window.draw(*tileShape);
        }
    }

    if (m_toggleBag)
    {
        m_window.draw(m_bagUI);
        drawGridAndTilesInBag(m_window, m_bagUI, tileBag);
    }

    drawGridAndTileInHolder(m_window, m_tileHolder[0], player1Hands);
    drawGridAndTileInHolder(m_window, m_tileHolder[1], player2Hands);
    m_window.draw(m_player1ScoreText);
    m_window.draw(m_player2ScoreText);
}

void Board::update()
{
    updateScores();
}

/// <summary>
/// init grid
/// </summary>
void Board::initializeGrid()
{
    gridRectangles.resize(row, std::vector<sf::RectangleShape>(col));

    const float rectSize = tileSize - 2;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            sf::RectangleShape rect(sf::Vector2f(rectSize, rectSize));
            rect.setPosition(j * tileSize + 1, i * tileSize + 1);

            if (j == col / 2 && i == row / 2) 
            {
                rect.setFillColor(sf::Color(200, 200, 200));
            }
            else 
            {
                rect.setFillColor(sf::Color::White);
            }
            rect.setOutlineThickness(1.0f);
            rect.setOutlineColor(sf::Color::Black);
            gridRectangles[i][j] = rect;
        }
    }
}

/// <summary>
/// fills the bag all the tiles that is eeded
/// </summary>
void Board::fillBag()
{
    const int numShapes = 6;
    const int numColors = 6;
    const int setsPerTile = 3;

    for (int i = 0; i < numShapes; ++i)
    {
        for (int j = 0; j < numColors; ++j)
        {
            for (int k = 0; k < setsPerTile; ++k)
            {
                Tile tile;
                tile.setShape(static_cast<TileShape>(i + 1));
                tile.setColor(static_cast<TileColor>(j + 1));

                tileBag.push_back(tile);
            }
        }
    }
}

/// <summary>
/// Gets random tiles inside the holder
/// </summary>
void Board::randomTilesInHolder()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, static_cast<int>(tileBag.size()) - 1);

    const int maxTilesPerPlayer = 6;

    while (!tileBag.empty() && (player1Hands.size() < maxTilesPerPlayer || player2Hands.size() < maxTilesPerPlayer))
    {
        if (player1Hands.size() < maxTilesPerPlayer)
        {
            if (!tileBag.empty()) 
            {
                int randomIndex = dis(gen);
                if (randomIndex >= 0 && randomIndex < static_cast<int>(tileBag.size())) 
                {
                    player1Hands.push_back(tileBag[randomIndex]);
                    tileBag.erase(tileBag.begin() + randomIndex);
                }
            }
        }
        if (player2Hands.size() < maxTilesPerPlayer)
        {
            if (!tileBag.empty()) 
            {
                int randomIndex = dis(gen);
                if (randomIndex >= 0 && randomIndex < static_cast<int>(tileBag.size()))
                {
                    player2Hands.push_back(tileBag[randomIndex]);
                    tileBag.erase(tileBag.begin() + randomIndex);
                }
            }
        }
    }
    std::cout << "Tiles in tile bag after distribution: " << tileBag.size() << std::endl;
}

/// <summary>
/// draws the tiles and the grid inside the holder
/// </summary>
/// <param name="m_window"></param>
/// <param name="tileHolder"></param>
/// <param name="tiles"></param>
void Board::drawGridAndTileInHolder(sf::RenderWindow& m_window, const sf::RectangleShape& tileHolder, const std::vector<Tile>& tiles)
{
    const float cellSize = 40.0f;
    const float tileSpacing = 10.0f;

    const float holderX = tileHolder.getPosition().x - tileHolder.getSize().x / 2.0f + 5;
    const float holderY = tileHolder.getPosition().y - tileHolder.getSize().y / 2.0f;

    for (size_t i = 0; i < tiles.size(); ++i)
    {
        float posX = holderX + i * (cellSize + tileSpacing);
        float posY = holderY + 30;

        HolderCell cell(sf::Vector2f(posX, posY), cellSize);
        cells.push_back(cell);

        m_window.draw(cell.cell);

        sf::Shape* tileShape = tiles[i].getTileShape();
        if (tileShape)
        {
            float tileX = posX + 20;
            float tileY = posY + 20;

            tileShape->setPosition(tileX, tileY);
            m_window.draw(*tileShape);
        }
    }

    for (size_t i = 0; i < cells.size(); ++i)
    {
        if (cells[i].selected)
        {
            cells[i].cell.setOutlineColor(sf::Color::Yellow);
            m_window.draw(cells[i].cell);
        }
    }
}

/// <summary>
/// draws the stuff inside the bag
/// </summary>
/// <param name="m_window"></param>
/// <param name="bagUI"></param>
/// <param name="tileBag"></param>
void Board::drawGridAndTilesInBag(sf::RenderWindow& m_window, const sf::RectangleShape& bagUI, const std::vector<Tile>& tileBag)
{
    const float startX = bagUI.getPosition().x - bagUI.getSize().x / 2.0f + 20.0f;
    const float startY = bagUI.getPosition().y - bagUI.getSize().y / 2.0f + 20.0f;
    const int maxCols = static_cast<int>(bagUI.getSize().x - 40.0f) / 50;
    const int maxRows = static_cast<int>(bagUI.getSize().y - 40.0f) / 50;

    float cellSize = 50.0f;
    float tileSpacingX = (bagUI.getSize().x - 40.0f - (maxCols * cellSize)) / (maxCols - 1);
    float tileSpacingY = (bagUI.getSize().y - 40.0f - (maxRows * cellSize)) / (maxRows - 1);

    float tileSize = 0.0f;

    int currentCol = 0;
    int currentRow = 0;

    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
    cell.setFillColor(sf::Color::Transparent);
    cell.setOutlineThickness(1.0f);
    cell.setOutlineColor(sf::Color::White);

    for (int row = 0; row < maxRows; ++row)
    {
        for (int col = 0; col < maxCols; ++col)
        {
            float posX = startX + col * (cellSize + tileSpacingX);
            float posY = startY + row * (cellSize + tileSpacingY);

            cell.setPosition(posX, posY);
            m_window.draw(cell);
        }
    }

    int tileCount = 0;
    for (const auto& tile : tileBag)
    {
        if (tileCount >= maxRows * maxCols)
        {
            break; // Limit reached, exit loop
        }

        sf::Shape* tileShape = tile.getTileShape();
        if (tileShape)
        {
            float posX = startX + currentCol * (cellSize + tileSpacingX) + (cellSize - tileSize) / 2.0f;
            float posY = startY + currentRow * (cellSize + tileSpacingY) + (cellSize - tileSize) / 2.0f;

            tileShape->setPosition(posX, posY);
            m_window.draw(*tileShape);

            currentCol++;
            if (currentCol >= maxCols)
            {
                currentCol = 0;
                currentRow++;
            }

            tileCount++;
        }
    }
}

/// <summary>
/// This is for selecting the tile from the holder and placing it down
/// </summary>
/// <param name="mousePosition"> mouse position </param>
/// <param name="currentPlayer"> which player </param>
void Board::selectedTile(sf::Vector2f mousePosition, int currentPlayer)
{
    if (currentPlayer == 1 && m_tileHolder[0].getGlobalBounds().contains(mousePosition))
    {
        for (size_t i = 0; i < player1Hands.size(); ++i)
        {
            posX = m_tileHolder[0].getPosition().x - m_tileHolder[0].getSize().x / 2.0f + i * (40.0f + 10.0f) + 20.0f;
            posY = m_tileHolder[0].getPosition().y - m_tileHolder[0].getSize().y / 2.0f + 30.0f;

            sf::FloatRect tileBounds(posX, posY, 40.0f, 40.0f);

            if (tileBounds.contains(mousePosition))
            {
                std::cout << "\nTile " << i << " selected from Player 1's holder" << std::endl;
                std::cout << "Shape: " << (player1Hands[i].getShapeAsString()) << ", Color: " << (player1Hands[i].getColorAsString()) << std::endl;

                cells[i].selected = true;
                selectedTileIndex = i;
                tileSelected = true;
            }
            else
            {
                cells[i].selected = false;
            }
        }
    }
    else if (currentPlayer == 2 && m_tileHolder[1].getGlobalBounds().contains(mousePosition))
    {
        for (size_t i = 0; i < player2Hands.size(); ++i)
        {
            posX = m_tileHolder[1].getPosition().x - m_tileHolder[1].getSize().x / 2.0f + i * (40.0f + 10.0f) + 20.0f;
            posY = m_tileHolder[1].getPosition().y - m_tileHolder[1].getSize().y / 2.0f + 30.0f;

            sf::FloatRect tileBounds(posX, posY, 40.0f, 40.0f);

            if (tileBounds.contains(mousePosition))
            {
                std::cout << "\nTile " << i << " selected from Player 2's holder" << std::endl;
                std::cout << "Shape: " << (player2Hands[i].getShapeAsString()) << ", Color: " << (player2Hands[i].getColorAsString()) << std::endl;

                cells[i].selected = true;
                selectedTileIndex = i;
                tileSelected = true;
            }
            else
            {
                cells[i].selected = false;
            }
        }
    }
    if (tileSelected)
    {
        sf::Vector2i gridPosition = getGridPosition(mousePosition);
        newGridPosition = gridPosition;
        if (isValidPlacement(gridPosition, currentPlayer))
        {
            float posX = gridPosition.x * tileSize + 25;
            float posY = gridPosition.y * tileSize + 25;
            gridRectangles[gridPosition.y][gridPosition.x].setFillColor(sf::Color::Black);
            if (currentPlayer == 1)
            {
                tileShape = player1Hands[selectedTileIndex].getTileShape();
            }
            else
            {
                tileShape = player2Hands[selectedTileIndex].getTileShape();
            }
            if (tileShape)
            {
                tileShape->setPosition(posX, posY);
                if (currentPlayer == 1)
                {
                    player1Hands[selectedTileIndex].setPosition(newGridPosition);
                    tilesOnBoard.push_back(player1Hands[selectedTileIndex]);
                }
                else
                {
                    player2Hands[selectedTileIndex].setPosition(newGridPosition);
                    tilesOnBoard.push_back(player2Hands[selectedTileIndex]);
                }

                if (currentPlayer == 1 && selectedTileIndex >= 0 && selectedTileIndex < player1Hands.size()
                    || currentPlayer == 2 && selectedTileIndex >= 0 && selectedTileIndex < player2Hands.size())
                {
                    if (currentPlayer == 1)
                    {
                        player1Hands.erase(player1Hands.begin() + selectedTileIndex);
                    }
                    else
                    {
                        player2Hands.erase(player2Hands.begin() + selectedTileIndex);
                    }
                    cells[selectedTileIndex].selected = false;
                    selectedTileIndex = -1;
                    tileSelected = false;
                }
                else
                {
                    std::cout << "Error: Invalid selected tile index" << std::endl;
                }
            }
            int score = calculateScoreForPlacement(newGridPosition, currentPlayer);
            if (currentPlayer == 1) 
            {
                player1Score += score;
            }
            else 
            {
                player2Score += score;
            }
        }
    }
    playerTurn = currentPlayer;
}

/// <summary>
/// Makes sure the the placement is valid
/// </summary>
/// <param name="gridPosition"></param>
/// <returns> true or false </returns>
bool Board::isValidPlacement(sf::Vector2i gridPosition, int currentPlayer)
{
    if (startingGame) // Only happens once
    {
        if (gridPosition.x == col / 2 && gridPosition.y == row / 2) 
        {
            startingGame = false;
            return true;
        }
        return false;
    }
    else 
    {
        if (currentPlayer == 1)
        {
            currentTile = player1Hands[selectedTileIndex];
        }
        else
        {
            currentTile = player2Hands[selectedTileIndex];
        }

        bool leftLine = checkLine(gridPosition, currentTile, sf::Vector2i(-1, 0));
        bool rightLine = checkLine(gridPosition, currentTile, sf::Vector2i(1, 0));
        bool upLine = checkLine(gridPosition, currentTile, sf::Vector2i(0, -1));
        bool downLine = checkLine(gridPosition, currentTile, sf::Vector2i(0, 1));

        // Check adjacent lines in all directions
        bool adjacentLinesValid = checkAdjacentLines(gridPosition, currentTile);

        if (adjacentLinesValid && (leftLine && rightLine && upLine && downLine))
        {
            std::cout << "\nValid line formed" << std::endl;
            return true;
        }
        return false;
    }
}

/// <summary>
/// Checks if there is a tile adjacent
/// </summary>
/// <param name="gridPosition"></param>
/// <returns></returns>
bool Board::checkAdjacentLines(sf::Vector2i gridPosition, const Tile& currentTile)
{
    sf::Vector2i adjacentPositions[] = 
    {
         {gridPosition.x, gridPosition.y - 1}, // above
         {gridPosition.x, gridPosition.y + 1}, // below
         {gridPosition.x - 1, gridPosition.y}, // left
         {gridPosition.x + 1, gridPosition.y}  // right
    };

    for (const auto& position : adjacentPositions) 
    {
        // Check if the position is within the board boundaries
        if (position.x >= 0 && position.x < col && position.y >= 0 && position.y < row) 
        {
            for (const auto& tile : tilesOnBoard) 
            {
                sf::Vector2i tilePosition = tile.getPosition();
                if (position == tilePosition) 
                {
                    // Compare color or shape of the current tile with the adjacent tile
                    if (currentTile.getColor() == tile.getColor()) 
                    {
                        std::cout << "Adjacent tile shares color" << std::endl;
                        return true;
                    }
                    else if (currentTile.getShape() == tile.getShape()) 
                    {
                        std::cout << "Adjacent tile shares shape" << std::endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

/// <summary>
/// Checks the lines if they are valid
/// </summary>
/// <param name="gridPosition"> tiles position on grid </param>
/// <param name="currentTile"> that current tile being selected </param>
/// <param name="direction"> which direction </param>
/// <returns></returns>
bool Board::checkLine(const sf::Vector2i& gridPosition, const Tile& currentTile, const sf::Vector2i& direction)
{
    int countColor = 0;
    int countShape = 0;
    bool lineDetected = false;

    std::vector<Tile> lineTiles;

    for (int i = 1; i <= 5; ++i)
    {
        int x = gridPosition.x + i * direction.x;
        int y = gridPosition.y + i * direction.y;

        if (x < 0 || x >= col || y < 0 || y >= row)
        {
            break; // reached board boundary
        }

        bool tileFound = false;
        for (const auto& tile : tilesOnBoard)
        {
            sf::Vector2i tilePosition = tile.getPosition();
            if (tilePosition.x == x && tilePosition.y == y) 
            {
                lineTiles.push_back(tile);
                tileFound = true;
            }
        }

        if (!tileFound)
        {
            break; // break if a gap in the line is found
        }
    }

    // Check if the line exists and the current tile can be placed in it
    if (!lineTiles.empty())
    {
        for (const auto& tile : lineTiles) 
        {
            if (tile.getColor() == currentTile.getColor()) 
            {
                countColor++;
            }
            if (tile.getShape() == currentTile.getShape())
            {
                countShape++;
            }
        }
        lineDetected = (countColor == lineTiles.size() || countShape == lineTiles.size());
    }
    else
    {
        return !lineDetected;
    }
    return lineDetected;
}

/// <summary>
/// gets the grid position
/// </summary>
/// <param name="mousePosition"></param>
/// <returns></returns>
sf::Vector2i Board::getGridPosition(sf::Vector2f mousePosition)
{
    int gridX = static_cast<int>(mousePosition.x / tileSize);
    int gridY = static_cast<int>(mousePosition.y / tileSize);
    return sf::Vector2i(gridX, gridY);
}

/// <summary>
/// init UI 
/// </summary>
void Board::setupUI()
{
    m_bottomUI.setFillColor(sf::Color::Cyan);
    m_bottomUI.setOutlineColor(sf::Color::Red);
    m_bottomUI.setOutlineThickness(1);
    m_bottomUI.setSize(sf::Vector2f(1200, 150));
    m_bottomUI.setPosition(sf::Vector2f(Global::S_WIDTH / 2, Global::S_HEIGHT - 150));
    m_bottomUI.setOrigin(m_bottomUI.getSize().x / 2, 0);

    m_seperationLineUI.setFillColor(sf::Color::Black);
    m_seperationLineUI.setSize(sf::Vector2f(10, 65));
    m_seperationLineUI.setPosition(sf::Vector2f(Global::S_WIDTH / 2, Global::S_HEIGHT - 65));
    m_seperationLineUI.setOrigin(m_seperationLineUI.getSize().x / 2, 0);

    m_boxBagForTextUI.setFillColor(sf::Color::Black);
    m_boxBagForTextUI.setSize(sf::Vector2f(100, 85));
    m_boxBagForTextUI.setPosition(sf::Vector2f(Global::S_WIDTH / 2, Global::S_HEIGHT - 150));
    m_boxBagForTextUI.setOrigin(m_boxBagForTextUI.getSize().x / 2, 0);

    sf::Color darkGreen(0, 100, 0);
    m_tileHolder[0].setFillColor(darkGreen);
    m_tileHolder[0].setOutlineColor(sf::Color::Red);
    m_tileHolder[0].setOutlineThickness(2);
    m_tileHolder[0].setSize(sf::Vector2f(300, 50));
    m_tileHolder[0].setPosition(sf::Vector2f(Global::S_WIDTH / 4, Global::S_HEIGHT - 100));
    m_tileHolder[0].setOrigin(m_tileHolder[0].getSize().x / 2, 0);

    m_tileHolder[1].setFillColor(darkGreen);
    m_tileHolder[1].setOutlineColor(sf::Color::Red);
    m_tileHolder[1].setOutlineThickness(2);
    m_tileHolder[1].setSize(sf::Vector2f(300, 50));
    m_tileHolder[1].setPosition(sf::Vector2f(Global::S_WIDTH / 2 + 300, Global::S_HEIGHT - 100));
    m_tileHolder[1].setOrigin(m_tileHolder[1].getSize().x / 2, 0);

    m_bagUI.setFillColor(sf::Color::Black);
    m_bagUI.setOutlineColor(sf::Color::Red);
    m_bagUI.setOutlineThickness(3);
    m_bagUI.setSize(sf::Vector2f(650, 800));
    m_bagUI.setPosition(sf::Vector2f(Global::S_WIDTH / 2, (Global::S_HEIGHT / 2) - 100));
    m_bagUI.setOrigin(m_bagUI.getSize().x / 2, m_bagUI.getSize().y / 2);

    // score text
    m_player1ScoreText.setFont(m_ArialBlackfont);
    m_player1ScoreText.setCharacterSize(24);
    m_player1ScoreText.setFillColor(sf::Color::Black);
    m_player1ScoreText.setPosition(sf::Vector2f(Global::S_WIDTH / 4 - 70, Global::S_HEIGHT - 140));

    m_player2ScoreText.setFont(m_ArialBlackfont);
    m_player2ScoreText.setCharacterSize(24);
    m_player2ScoreText.setFillColor(sf::Color::Black);
    m_player2ScoreText.setPosition(sf::Vector2f(Global::S_WIDTH * 3 / 4 - 70, Global::S_HEIGHT - 140));
}

void Board::setupFontAndText()
{
    if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
    {
        std::cout << "problem loading arial black font" << std::endl;
    }
    m_bagText.setFont(m_ArialBlackfont);
    m_bagText.setStyle(sf::Text::Italic);
    m_bagText.setCharacterSize(20U);
    m_bagText.setFillColor(sf::Color::White);
}

void Board::updateScores() 
{
    m_player1ScoreText.setString("Player 1: " + std::to_string(player1Score));
    m_player2ScoreText.setString("Player 2: " + std::to_string(player2Score));
}

/// <summary>
/// opens and closes the bag
/// </summary>
void Board::toggleBag()
{
    std::cout << "\nbag opened" << std::endl;
    m_toggleBag = !m_toggleBag;
}

/// <summary>
/// after ending turn you get random tiles from the bag to your holder
/// </summary>
void Board::endTurn()
{
    randomTilesInHolder();
}

/// <summary>
/// very basic move for AI
/// finds a valid placement for a tile in its hand
/// </summary>
void Board::AITurn() 
{
    sf::Vector2i gridPosition(-1, -1); // Initialize with invalid position

    // Loop through the tiles in player2Hands for AI
    for (size_t i = 0; i < player2Hands.size(); ++i) 
    {
        // Check each tile against each position on the board
        for (int x = 0; x < col; ++x) 
        {
            for (int y = 0; y < row; ++y) 
            {
                sf::Vector2i currentPos(x, y);
                selectedTileIndex = i;
                if (isValidPlacement(currentPos, 2)) 
                {
                    // If placement is valid, set the gridPosition and break the loops
                    gridPosition = currentPos;
                    break;
                }
            }
            if (gridPosition != sf::Vector2i(-1, -1)) 
            {
                break;
            }
        }
        if (gridPosition != sf::Vector2i(-1, -1))
        {
            // If a valid position is found, place the tile and break the loop
            float posX = gridPosition.x * tileSize + 25;
            float posY = gridPosition.y * tileSize + 25;

            gridRectangles[gridPosition.y][gridPosition.x].setFillColor(sf::Color::Black);

            tileShape = player2Hands[i].getTileShape();
            if (tileShape) 
            {
                tileShape->setPosition(posX, posY);
                player2Hands[i].setPosition(gridPosition);
                tilesOnBoard.push_back(player2Hands[i]);

                player2Hands.erase(player2Hands.begin() + i);
                cells[selectedTileIndex].selected = false;
                selectedTileIndex = -1;
                tileSelected = false;
            }
            int score = calculateScoreForPlacement(gridPosition, 2);
            player2Score += score;
            break;
        }
    }
}

/// <summary>
/// Makes the AI place all the available tiles it has in its hand
/// </summary>
void Board::AIMultiplePlacements()
{
    bool placedTile = false;

    // Loop through the tiles in player2Hands
    for (size_t i = 0; i < player2Hands.size(); ++i)
    {
        bool foundPosition = false;

        // Check each tile against each position on the board
        for (int x = 0; x < col; ++x)
        {
            for (int y = 0; y < row; ++y)
            {
                sf::Vector2i currentPos(x, y);
                selectedTileIndex = i;
                if (isValidPlacement(currentPos, 2))
                {
                    float posX = currentPos.x * tileSize + 25;
                    float posY = currentPos.y * tileSize + 25;

                    gridRectangles[currentPos.y][currentPos.x].setFillColor(sf::Color::Black);

                    sf::Shape* tileShape = player2Hands[i].getTileShape();
                    if (tileShape)
                    {
                        tileShape->setPosition(posX, posY);
                        player2Hands[i].setPosition(currentPos);
                        tilesOnBoard.push_back(player2Hands[i]);
                        foundPosition = true;
                        placedTile = true;
                        int score = calculateScoreForPlacement(currentPos, 2);
                        player2Score += score;
                        break;
                    }
                }
            }
            if (foundPosition)
            {
                break;
            }
        }
    }

    // Remove all placed tiles from player2Hands
    if (placedTile)
    {
        player2Hands.erase(std::remove_if(player2Hands.begin(), player2Hands.end(),
            [&](const Tile& tile)
            {
                return std::find(tilesOnBoard.begin(), tilesOnBoard.end(), tile) != tilesOnBoard.end();
            }),
            player2Hands.end());
    }
}

//void Board::MiniMax()
//{
//
//}

int Board::miniMax(int depth, bool maximizingPlayer) 
{
    if (depth == 0/* || gameIsOver()*/)
    {
        return evaluateBoard();
    }

    if (maximizingPlayer) 
    {
        int maxEval = std::numeric_limits<int>::min();
       
        return maxEval;
    }
    else 
    {
        int minEval = std::numeric_limits<int>::max();
        
        return minEval;
    }
}

int Board::evaluateBoard() 
{
    
}

void Board::findBestMove()
{
    int bestEval = std::numeric_limits<int>::min();
}

/// <summary>
/// caculates the score based on where it is.
/// is it connected to a line
/// </summary>
/// <param name="gridPosition"></param>
/// <param name="currentPlayer"></param>
/// <returns></returns>
int Board::calculateScoreForPlacement(const sf::Vector2i& gridPosition, int currentPlayer) 
{
    int score = 0;

    // Check for horizontal line
    int horizontalCount = 1;
    for (int i = gridPosition.x - 1; i >= 0; --i)
    {
        if (isSameTile(gridPosition.y, i, currentPlayer))
        {
            horizontalCount++;
        }
        else 
        {
            break;
        }
    }
    for (int i = gridPosition.x + 1; i < col; ++i)
    {
        if (isSameTile(gridPosition.y, i, currentPlayer))
        {
            horizontalCount++;
        }
        else 
        {
            break;
        }
    }

    // Check for vertical line
    int verticalCount = 1;
    for (int i = gridPosition.y - 1; i >= 0; --i)
    {
        if (isSameTile(i, gridPosition.x, currentPlayer))
        {
            verticalCount++;
        }
        else 
        {
            break;
        }
    }
    for (int i = gridPosition.y + 1; i < row; ++i)
    {
        if (isSameTile(i, gridPosition.x, currentPlayer)) 
        {
            verticalCount++;
        }
        else 
        {
            break;
        }
    }
    // Calculate score based on line count
    score = (horizontalCount > 1 ? horizontalCount : 0) + (verticalCount > 1 ? verticalCount : 0);

    return score;
}

/// <summary>
/// checks if its the same tile players or enemies
/// </summary>
/// <param name="y"></param>
/// <param name="x"></param>
/// <param name="currentPlayer"></param>
/// <returns></returns>
bool Board::isSameTile(int y, int x, int currentPlayer)
{
    sf::Vector2i position(x, y);
    const std::vector<Tile>& currentHands = (currentPlayer == 1) ? player1Hands : player2Hands;

    for (const auto& tile : tilesOnBoard) 
    {
        if (tile.getPosition() == position)
        {
            return true;
        }
    }

    for (const auto& tile : currentHands)
    {
        if (tile.getPosition() == position) 
        {
            return true;
        }
    }
    return false;
}