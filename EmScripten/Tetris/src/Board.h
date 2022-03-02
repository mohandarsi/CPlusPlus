#pragma once
#include "raylib-cpp.hpp"

#include <vector>
#include "Cell.h"
#include "utils.h"

class Block;

class Board
{
public:
    Board(int hCells, int vCells, int cellSize);
    void draw(const raylib::Vector2& location);
    void placeBlock(const Block& block);
    bool collides(const Block& block) const;
    
    GETTER(int, NumberOfHCells,m_hCells)
    GETTER(int, NumberOfVCells,m_vCells)
    GETTER(int, CellSize,m_cellSize)
    
private:
    void drawGrid(const raylib::Vector2& location);

private:
    int m_hCells, m_vCells, m_cellSize;
    std::vector<std::vector<Cell>> m_cellMatrix;

};
