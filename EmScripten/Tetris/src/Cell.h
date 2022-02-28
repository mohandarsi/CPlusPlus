#pragma once

#include "raylib-cpp.hpp"

class Cell
{
public:
    Cell();
    Cell(const Color& color, unsigned size);
    void draw(const raylib::Vector2& position, bool shallow) const;
    static void draw(const raylib::Vector2& position, const Color& color, bool shallow);

private:
    Color m_color;
    unsigned m_size;
};
