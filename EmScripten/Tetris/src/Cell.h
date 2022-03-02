#pragma once

#include "raylib-cpp.hpp"
#include "utils.h"

class Cell
{
public:
    Cell();
    Cell(const Color& color, unsigned size);
    void draw(const raylib::Vector2& position, bool shallow) const;
    static void draw(const raylib::Vector2& position, const Color& color, bool shallow);

    GETTER(const Color&, Color, m_color)
    SETTER(Color, Color, m_color)


private:
    Color m_color;
    unsigned m_size;
};
