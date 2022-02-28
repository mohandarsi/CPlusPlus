#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

#include "Game.h"
#include "Const.h"

//static variable initialization
float Timer::m_fameTime = GetTime();

const raylib::Vector2 BoardOffset(GRID_OFFSET_X, GRID_OFFSET_Y);

Game::Game(int width, int height)
    : m_window(width, height, "Tetris") 
    , m_board(HORZ_CELLS,VERT_CELLS,CELL_SIZE)
    , m_currentPiece(Piece::createRandomPiece(m_board))
{
    m_slideTimer.restart();
}

void RenderLoopCallback(void* arg)
{
  static_cast<Game*>(arg)->gameLoop();
}

void Game::run()
{
    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop_arg(RenderLoopCallback,this, 0, 1);
    #else
        SetTargetFPS(60);
        while (!m_window.ShouldClose())
        {
            gameLoop();
        }
    #endif
}

void Game::gameLoop()
{
    Timer::updateFrame();
    input();
    update();
    draw();
}

void Game::input()
{

}

void Game::update()
{
    //slide down automatically
    const auto  slideInterval = 0.5;

    if (m_slideTimer.elapsed() >= slideInterval)
    {
        m_slideTimer.restart();
        slideCurrentPiece( raylib::Vector2 { 0, 1 });
    }
}

void Game::slideCurrentPiece(const raylib::Vector2& normalizedPosition)
{
    m_currentPiece->translate(normalizedPosition);
    if(m_currentPiece->collides())
       m_currentPiece = Piece::createRandomPiece(m_board);
}

void Game::drawPiece()
{
    const raylib::Vector2 pieceRelaiveLocation = m_currentPiece->getPosition() * m_board.getCellSize();
    const raylib::Vector2 locationTodraw = BoardOffset + pieceRelaiveLocation;

    m_currentPiece->draw(locationTodraw, false);
}

void Game::draw()
{
    BeginDrawing();

        m_window.ClearBackground(BLACK);

        m_board.draw(BoardOffset);

        drawPiece();

        DrawFPS(10, 10);

    EndDrawing();

}
