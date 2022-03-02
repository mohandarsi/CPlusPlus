#include "Board.h"

#include "Const.h"
#include "Block.h"

Board::Board(int hCells, int vCells, int cellSize) :
    m_hCells(hCells),
    m_vCells(vCells),
    m_cellSize(cellSize + CELL_MARGIN_THICKNESS),
    m_cellMatrix(vCells, std::vector<Cell>(hCells,Cell(BLANK,m_cellSize)))
{
}

bool Board::collides(const Block& block) const
{
    const auto& layout = block.getLayout();
    const auto& position = block.getPosition();

    for(auto iy=0;iy < layout.size ;iy++)
    {
        for(auto ix=0; ix < layout.size ;ix++)
        {
            const auto tx= position.x+ix; 
            const auto ty = position.y+iy;

            if(layout.layout[iy][ix] != 0)
            {
                if(tx < 0 || tx >= m_hCells || ty< 0 || ty>= m_vCells)
                    return true;

                if(m_cellMatrix[ty][tx].getColor().a != 0)
                     return true;
            }
        }
    }
    return false;
}

void Board::placeBlock(const Block& block)
{ 
    const auto& layout = block.getLayout();
    const auto& color = block.getcolor();
    const auto& position = block.getPosition();

    for (unsigned iy = 0; iy < layout.size; ++iy)
    {
        for (unsigned ix = 0; ix < layout.size; ++ix)
        {
            const auto tx= position.x+ix; 
            const auto ty = position.y+iy;
            if(layout.layout[iy][ix] != 0x0)
            {
                m_cellMatrix[ty][tx].setColor(color);
            }
        }
    }
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

