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
    , m_currentBlock(Block::createRandomBlock(m_board))
{
    m_slideTimer.restart();
    m_xmoveTimer.restart();
    m_ymoveTimer.restart();
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
    constexpr auto XMOVE_COOLDOWN = 0.08;
    constexpr auto YMOVE_COOLDOWN = 0.05;
    constexpr auto SLIDE_INTERVAL = 0.5;

    if(m_xmoveTimer.elapsed() >= XMOVE_COOLDOWN)
    {
       if(IsKeyDown(KEY_LEFT))
       {
          m_xmoveTimer.restart();
          moveCurrentBlock(raylib::Vector2 {-1, 0});
       }
       else if(IsKeyDown(KEY_RIGHT))
       {
           m_xmoveTimer.restart();
           moveCurrentBlock(raylib::Vector2 {1, 0});
       }
    }

    if(m_ymoveTimer.elapsed() >= YMOVE_COOLDOWN)
    {
       if(IsKeyDown(KEY_DOWN))
       {
          m_ymoveTimer.restart();
          m_slideTimer.restart();
          const auto slided = moveCurrentBlock( raylib::Vector2 { 0, 1 });
          if(!slided) placeCurrentBlock();
       }
    }

    if(IsKeyPressed(KEY_UP))
    {
        m_currentBlock->rotateLeft();
    }

    //slide down automatically

    if (m_slideTimer.elapsed() >= SLIDE_INTERVAL)
    {
        m_slideTimer.restart();
        const auto slided = moveCurrentBlock( raylib::Vector2 { 0, 1 });
        if(!slided) placeCurrentBlock();
    }
}
void Game::placeCurrentBlock()
{
    m_board.placeBlock(*m_currentBlock.get());
    m_currentBlock = Block::createRandomBlock(m_board);
}

bool Game::moveCurrentBlock(const raylib::Vector2& normalizedPosition)
{
    m_currentBlock->translate(normalizedPosition);
    if(m_board.collides(*m_currentBlock.get()))
    {
        //undo the translation and return
        m_currentBlock->translate(-normalizedPosition);
        return false;
    }
    return true;
}

void Game::drawBlock()
{
    const raylib::Vector2 blockRelaiveLocation = m_currentBlock->getPosition() * m_board.getCellSize();
    const raylib::Vector2 locationTodraw = BoardOffset + blockRelaiveLocation;

    m_currentBlock->draw(locationTodraw, false);
}

void Game::draw()
{
    BeginDrawing();

        m_window.ClearBackground(BLACK);

        m_board.draw(BoardOffset);

        drawBlock();

        DrawFPS(10, 10);

    EndDrawing();

}
