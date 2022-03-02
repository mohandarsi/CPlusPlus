#pragma once
#include "raylib-cpp.hpp"

#include<memory>

#include "Board.h"
#include "Block.h"
#include "Timer.h"

class Game
{
public:
	Game(int width, int height);
	void run();
	void gameLoop();

private:
	void input();
	void update();
	void draw();
	void drawBlock();
	bool moveCurrentBlock(const raylib::Vector2& normalizedPosition);
	void placeCurrentBlock();

private:
	raylib::Window m_window;
	Board m_board;
	std::unique_ptr<Block> m_currentBlock;
	Timer m_slideTimer;
	Timer m_xmoveTimer;
	Timer m_ymoveTimer;
};
