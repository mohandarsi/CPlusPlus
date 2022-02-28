#pragma once
#include "raylib-cpp.hpp"

#include <array>
#include <memory>

enum class PieceName
{
	I_BLOCK,
	J_BLOCK,
	L_BLOCK,
	O_BLOCK,
	S_BLOCK,
	T_BLOCK,
	Z_BLCOK
};

struct PieceLayout
{
	unsigned size;
	std::array<std::array<int, 4>, 4> layout;
	//unsigned layout[4][4];
	unsigned width;
	unsigned height;
};

class Board;

class Piece
{
	
public:
	Piece(const Board& m_board, const PieceName name, const Color& color);

	static std::unique_ptr<Piece> createRandomPiece(const Board& m_board);
	
	bool collides() const;
	void rotateRight();
	void rotateLeft();
	void translate(const raylib::Vector2& translation);
	void draw(const raylib::Vector2& location, bool shallow);
	const raylib::Vector2& getPosition() const  {return m_position;}

private:
    const Board& m_board;
	raylib::Vector2 m_position;
	Color m_color;
	PieceLayout m_layout;
};

