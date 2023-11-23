#include "Board.h"

Board::Board()
{
	initializeGrid();
	populateGridRandomly();
}

Board::~Board()
{
}

void Board::render(sf::RenderWindow& m_window)
{
    for (int i = 0; i <= row; ++i) 
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(0, i * tileSize)),
            sf::Vertex(sf::Vector2f(col * tileSize, i * tileSize))
        };
        m_window.draw(line, 2, sf::Lines);
    }
    for (int j = 0; j <= col; ++j) 
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(j * tileSize, 0)),
            sf::Vertex(sf::Vector2f(j * tileSize, row * tileSize))
        };
        m_window.draw(line, 2, sf::Lines);
    }

    for (int i = 0; i < row; ++i) 
    {
        for (int j = 0; j < col; ++j) 
        {
            sf::Shape* tileShape = m_tiles[i][j].getTileShape();
            if (tileShape) 
            {
                tileShape->setPosition(j * tileSize, i * tileSize);
                m_window.draw(*tileShape);
            }
        }
    }
}

void Board::initializeGrid()
{
    m_tiles.resize(row, std::vector<Tile>(col));
}

void Board::populateGridRandomly()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> shapeDist(1, 6);
    std::uniform_int_distribution<> colorDist(1, 6);

    std::vector<std::pair<int, int>> positionsFilled;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            bool positionFilled = false;
            for (const auto& pos : positionsFilled)
            {
                if (pos.first == i && pos.second == j)
                {
                    positionFilled = true;
                    break;
                }
            }

            if (!positionFilled)
            {
                Tile tile;
                tile.setShape(static_cast<TileShape>(shapeDist(gen)));
                tile.setColor(static_cast<TileColor>(colorDist(gen)));
                m_tiles[i][j] = tile;
                positionsFilled.emplace_back(i, j);
            }
        }
    }
}

