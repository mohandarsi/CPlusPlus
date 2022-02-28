#include "Piece.h"
#include<map>
#include <random>
#include "Board.h"
#include "Cell.h"
#include "Const.h"

static const std::map<PieceName, PieceLayout> blockNameToLayOut =
{
     {
         PieceName::I_BLOCK, { 4, { { {0,0,0,0},
                                        {1,1,1,1},
                                        {0,0,0,0},
                                        {0,0,0,0} } }, 4, 3 }  },

     {
         PieceName::T_BLOCK, { 3, {  { {0,1,0,0},
                                   {1,1,1,0},
                                   {0,0,0,0},
                                   {0,0,0,0} }}, 3, 2 }  },

     {
         PieceName::S_BLOCK, { 3, { { {0,1,1,0},
                                  {1,1,0,0},
                                  {0,0,0,0},
                                  {0,0,0,0} } }, 3, 2 }  },

     {
         PieceName::O_BLOCK, { 2, { {{1,1,0,0},
                                  {1,1,0,0},
                                  {0,0,0,0},
                                  {0,0,0,0} }}, 2, 2 }  },

     {
         PieceName::Z_BLCOK, { 3, { {{1,1,0,0},
                                  {0,1,1,0},
                                  {0,0,0,0},
                                  {0,0,0,0} }}, 3, 2 }  },

     {
         PieceName::J_BLOCK, { 3, {{  {1,0,0,0},
                                   {1,1,1,0},
                                   {0,0,0,0},
                                   {0,0,0,0} }}, 3, 2 }  },

     {
         PieceName::L_BLOCK, { 3, { { {0,0,1,0},
                                   {1,1,1,0},
                                   {0,0,0,0},
                                   {0,0,0,0} }}, 3, 2 }  }

};


static constexpr std::array<Color,7> colors = { RED, BLUE, GREEN, LIGHTGRAY, SKYBLUE, PINK, PURPLE};

Piece::Piece(const Board& board,const PieceName name, const Color& color):
m_board{board},
m_position{},
m_color{color},
m_layout{blockNameToLayOut.at(name)}
{
}

void Piece::rotateLeft()
{
    const auto layout = m_layout.layout;
    for (unsigned ix = 0; ix < m_layout.size; ++ix)
        for (unsigned iy = 0; iy < m_layout.size; ++iy)
            m_layout.layout[ix][iy] = layout[iy][m_layout.size - 1 - ix];

}

void Piece::rotateRight()
{
    const auto layout = m_layout.layout;
    for (unsigned ix = 0; ix < m_layout.size; ++ix)
        for (unsigned iy = 0; iy < m_layout.size; ++iy)
            m_layout.layout[iy][m_layout.size - 1 - ix] = layout[ix][iy];
}

void Piece::translate(const raylib::Vector2& translation)
{
    m_position += translation;
}

void Piece::draw(const raylib::Vector2& location, bool shallow)
{
    const auto cellSize = m_board.getCellSize() ;

    for (unsigned iy = 0; iy < m_layout.size; ++iy)
    {
        for (unsigned ix = 0; ix < m_layout.size; ++ix)
        {
            if(m_layout.layout[iy][ix] != 0x0)
            {
                Cell c(m_color, m_board.getCellSize());
                //draw the cell relative position to the piece.
                raylib::Vector2 cellLocation = location +  raylib::Vector2{ ix * cellSize ,  iy * cellSize };
                c.draw(cellLocation, shallow);
            }
        }
    }
}

bool Piece::collides() const
{
    const auto hCells = m_board.getNumberOfHCells();
    const auto vCells = m_board.getNumberOfVCells();

    for(auto iy=0;iy < m_layout.size ;iy++)
    {
        for(auto ix=0; ix < m_layout.size ;ix++)
        {
            auto position = m_position + raylib::Vector2 {ix,iy};

            if(m_layout.layout[iy][ix] != 0)
            {
                if(position.x < 0 || position.x >= hCells || position.y < 0 || position.y >= vCells)
                    return true;
                // if(m_board.getCell(position.y,position.x).a != 0)
                //     return true;
            }
        }
    }
    return false;
}

std::unique_ptr<Piece> Piece::createRandomPiece(const Board& m_board)
{
    static std::default_random_engine generator;
    static std::uniform_int_distribution<int> pieceDist(0, blockNameToLayOut.size()-1);
    static std::uniform_int_distribution<int> colorDist(0, colors.size()-1);

    const auto blockName = static_cast<PieceName>(pieceDist(generator));
    const auto randomColor = colors[colorDist(generator)]; 

    auto piece = std::make_unique<Piece>(m_board,blockName, randomColor);

    raylib::Vector2 cellLocation;
    cellLocation.x = (m_board.getNumberOfHCells() - piece->m_layout.size) / 2;
    cellLocation.y = 0;
    piece->translate(cellLocation);

    return piece;
}
