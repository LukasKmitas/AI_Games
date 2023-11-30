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

    if (m_toggleBag)
    {
        m_window.draw(m_bagUI);
        drawGridAndTilesInBag(m_window, m_bagUI, tileBag);
    }

    drawGridAndTileInHolder(m_window, m_tileHolder[0], player1Hands);
    drawGridAndTileInHolder(m_window, m_tileHolder[1], Player2Hands);
}

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
            rect.setFillColor(sf::Color::White);
            gridRectangles[i][j] = rect;
        }
    }
}

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

void Board::randomTilesInHolder()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, static_cast<int>(tileBag.size()) - 1);

    const int maxTilesPerPlayer = 6;

    while (!tileBag.empty() && (player1Hands.size() < maxTilesPerPlayer || Player2Hands.size() < maxTilesPerPlayer))
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
        if (Player2Hands.size() < maxTilesPerPlayer)
        {
            if (!tileBag.empty()) 
            {
                int randomIndex = dis(gen);
                if (randomIndex >= 0 && randomIndex < static_cast<int>(tileBag.size()))
                {
                    Player2Hands.push_back(tileBag[randomIndex]);
                    tileBag.erase(tileBag.begin() + randomIndex);
                }
            }
        }
    }
    std::cout << "Tiles in tile bag after distribution: " << tileBag.size() << std::endl;
}

void Board::drawGridAndTileInHolder(sf::RenderWindow& m_window, const sf::RectangleShape& tileHolder, const std::vector<Tile>& tiles)
{
    const float cellSize = 40.0f;
    const float tileSpacing = 10.0f;

    const float holderX = tileHolder.getPosition().x - tileHolder.getSize().x / 2.0f + 5;
    const float holderY = tileHolder.getPosition().y - tileHolder.getSize().y / 2.0f;

    sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
    cell.setFillColor(sf::Color::Transparent);
    cell.setOutlineThickness(2.0f);
    cell.setOutlineColor(sf::Color::Black);

    for (size_t i = 0; i < tiles.size(); ++i)
    {
        float posX = holderX + i * (cellSize + tileSpacing);
        float posY = holderY + 30;

        cell.setPosition(posX, posY);
        m_window.draw(cell);

        sf::Shape* tileShape = tiles[i].getTileShape();
        if (tileShape)
        {
            float tileX = posX + 20;
            float tileY = posY + 20;

            tileShape->setPosition(tileX, tileY);
            m_window.draw(*tileShape);
        }
    }
}

void Board::drawGridAndTilesInBag(sf::RenderWindow& m_window, const sf::RectangleShape& bagUI, const std::vector<Tile>& tileBag)
{
    const float startX = bagUI.getPosition().x - bagUI.getSize().x / 2.0f + 20.0f;
    const float startY = bagUI.getPosition().y - bagUI.getSize().y / 2.0f + 20.0f;
    const int maxCols = static_cast<int>(bagUI.getSize().x - 40.0f) / 50;
    const int maxRows = static_cast<int>(bagUI.getSize().y - 40.0f) / 50;

    float cellSize = 50.0f;
    float tileSpacingX = (bagUI.getSize().x - 40.0f - (maxCols * cellSize)) / (maxCols - 1);
    float tileSpacingY = (bagUI.getSize().y - 40.0f - (maxRows * cellSize)) / (maxRows - 1);

    float tileSize = 0.0f; // Adjust tile size if needed

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
            float posX = startX + currentCol * (cellSize + tileSpacingX) + (cellSize - tileSize) / 2.0f; // Adjusted position for centering
            float posY = startY + currentRow * (cellSize + tileSpacingY) + (cellSize - tileSize) / 2.0f; // Adjusted position for centering

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

void Board::toggleBag()
{
    std::cout << "bag opened" << std::endl;
    m_toggleBag = !m_toggleBag;
}
