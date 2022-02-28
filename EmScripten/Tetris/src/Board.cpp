#include "Board.h"

#include "Const.h"
#include "Piece.h"

Board::Board(int hCells, int vCells, int cellSize) :
    m_hCells(hCells),
    m_vCells(vCells),
    m_cellSize(cellSize + CELL_MARGIN_THICKNESS),
    m_cellMatrix(vCells, std::vector<Cell>(hCells,Cell(BLANK,m_cellSize)))
{
}

void Board::drawGrid(const raylib::Vector2& location)
{
    const float boardWidth = m_cellSize * m_hCells;
    const float boardHeight = m_cellSize * m_vCells;

    constexpr Color GRID_COLOR = { 0x11, 0x11, 0x11, 0xff };
    // draw outer rectangle with filled color.
    DrawRectangleV(location, Vector2{ boardWidth, boardHeight }, GRID_COLOR);

    constexpr auto GAP_COLOR = DARKGRAY;

    // draw horizontal lines
    const  auto x = location.x;
    const  auto w = boardWidth;
    for (auto iy = 0; iy < m_vCells+1; ++iy)
    {
        const auto y = location.y + iy * m_cellSize;
        //DrawRectangle(x, y , w, gapLineWidth, GAP_COLOR);
        DrawLineEx(Vector2{ x,y }, Vector2{ x+w,y }, CELL_MARGIN_THICKNESS, GAP_COLOR);
    }

    const  auto y = location.y;
    const  auto h = boardHeight;
    for (auto ix = 0; ix <= m_hCells; ++ix)
    {
        const auto x = location.x + ix * m_cellSize;
        //DrawRectangle(x, y, gapLineWidth, h, GAP_COLOR);
        DrawLineEx(Vector2{ x,y }, Vector2{ x,y+h }, CELL_MARGIN_THICKNESS, GAP_COLOR);
    }

}

void Board::draw(const raylib::Vector2 &location)
{
    drawGrid(location);

    for (auto iy = 0; iy < m_vCells; ++iy)
    {
        for (auto ix = 0; ix < m_hCells; ++ix)
        {
            const auto drawAt = location + raylib::Vector2(ix * m_cellSize, iy * m_cellSize);

            m_cellMatrix[iy][ix].draw(drawAt, false);
        }

    }
}

