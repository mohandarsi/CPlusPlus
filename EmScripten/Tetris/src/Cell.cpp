#include "Cell.h"

Cell::Cell(): m_color{},
m_size(0)
{
}

Cell::Cell(const Color& color, unsigned size) :
    m_color(color),
    m_size(size)
{
}

void Cell::draw(const raylib::Vector2& position, bool shallow) const
{
    if (m_color.a == 0) return;

    const raylib::Rectangle rect{ position.x, position.y, m_size, m_size };

    if (!shallow)
        DrawRectangleRec(rect, Fade(m_color, 0.75));
    else
        DrawRectangleLinesEx(rect, 2, m_color);
}