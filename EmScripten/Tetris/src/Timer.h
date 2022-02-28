#pragma once
#include "raylib-cpp.hpp"

class Timer
{
    friend class Game;

public:

    float elapsed()
    {
        return m_fameTime - m_startTime;
    }
    void restart()
    {
        m_startTime = m_fameTime;
    }

private:
    static void updateFrame()
    {
        m_fameTime = GetTime();
    }

private:
    static float m_fameTime;
    float m_startTime;
};
