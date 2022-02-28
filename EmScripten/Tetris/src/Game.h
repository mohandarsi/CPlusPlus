#pragma once
#include "raylib-cpp.hpp"

#include<memory>

#include "Board.h"
#include "Piece.h"
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
	void drawPiece();
	void slideCurrentPiece(const raylib::Vector2& normalizedPosition);

private:
	raylib::Window m_window;
	Board m_board;
	std::unique_ptr<Piece> m_currentPiece;
	Timer m_slideTimer;
};
