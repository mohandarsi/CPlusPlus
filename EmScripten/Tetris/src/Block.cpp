#include "Block.h"
#include<map>
#include <ctime>
#include <cstdlib>
#include <random>
#include "Board.h"
#include "Cell.h"
#include "Const.h"

static const std::map<BlockName, BlockLayout> blockNameToLayOut =
{
     {
         BlockName::I_BLOCK, { 4, { { {0,0,0,0},
                                        {1,1,1,1},
                                        {0,0,0,0},
                                        {0,0,0,0} } }, 4, 3 }  },

     {
         BlockName::T_BLOCK, { 3, {  { {0,1,0,0},
                                   {1,1,1,0},
                                   {0,0,0,0},
                                   {0,0,0,0} }}, 3, 2 }  },

     {
         BlockName::S_BLOCK, { 3, { { {0,1,1,0},
                                  {1,1,0,0},
                                  {0,0,0,0},
                                  {0,0,0,0} } }, 3, 2 }  },

     {
         BlockName::O_BLOCK, { 2, { {{1,1,0,0},
                                  {1,1,0,0},
                                  {0,0,0,0},
                                  {0,0,0,0} }}, 2, 2 }  },

     {
         BlockName::Z_BLCOK, { 3, { {{1,1,0,0},
                                  {0,1,1,0},
                                  {0,0,0,0},
                                  {0,0,0,0} }}, 3, 2 }  },

     {
         BlockName::J_BLOCK, { 3, {{  {1,0,0,0},
                                   {1,1,1,0},
                                   {0,0,0,0},
                                   {0,0,0,0} }}, 3, 2 }  },

     {
         BlockName::L_BLOCK, { 3, { { {0,0,1,0},
                                   {1,1,1,0},
                                   {0,0,0,0},
                                   {0,0,0,0} }}, 3, 2 }  }

};


static constexpr std::array<Color,7> colors = { RED, BLUE, GREEN, LIGHTGRAY, MAROON, PINK, YELLOW};

Block::Block(const Board& board,const BlockName name, const Color& color):
m_board{board},
m_position{},
m_color{color},
m_layout{blockNameToLayOut.at(name)}
{
}

void Block::rotateLeft()
{
    const auto layout = m_layout.layout;
    for (unsigned ix = 0; ix < m_layout.size; ++ix)
        for (unsigned iy = 0; iy < m_layout.size; ++iy)
            m_layout.layout[ix][iy] = layout[iy][m_layout.size - 1 - ix];

}

void Block::rotateRight()
{
    const auto layout = m_layout.layout;
    for (unsigned ix = 0; ix < m_layout.size; ++ix)
        for (unsigned iy = 0; iy < m_layout.size; ++iy)
            m_layout.layout[iy][m_layout.size - 1 - ix] = layout[ix][iy];
}

void Block::translate(const raylib::Vector2& translation)
{
    m_position += translation;
}

void Block::draw(const raylib::Vector2& location, bool shallow)
{
    const auto cellSize = m_board.getCellSize() ;

    for (unsigned iy = 0; iy < m_layout.size; ++iy)
    {
        for (unsigned ix = 0; ix < m_layout.size; ++ix)
        {
            if(m_layout.layout[iy][ix] != 0x0)
            {
                Cell c(m_color, m_board.getCellSize());
                //draw the cell relative position to the blcok.
                raylib::Vector2 cellLocation = location +  raylib::Vector2{ ix * cellSize ,  iy * cellSize };
                c.draw(cellLocation, shallow);
            }
        }
    }
}

std::unique_ptr<Block> Block::createRandomBlock(const Board& m_board)
{
    static std::random_device randomDevice;
    static std::mt19937 blockGenerator(randomDevice()); 
    static std::mt19937 colorGenerator(randomDevice()); 
    static std::uniform_int_distribution<int> blockNameDist(0, blockNameToLayOut.size()-1);
    static std::uniform_int_distribution<int> colorDist(0, colors.size()-1);
  
    const auto blockName = static_cast<BlockName>(blockNameDist(blockGenerator));
    const auto randomColor = colors[colorDist(colorGenerator)]; 

    auto piece = std::make_unique<Block>(m_board,blockName, randomColor);

    raylib::Vector2 cellLocation;
    cellLocation.x = (m_board.getNumberOfHCells() - piece->m_layout.size) / 2;
    cellLocation.y = 0;
    piece->translate(cellLocation);

    return piece;
}

