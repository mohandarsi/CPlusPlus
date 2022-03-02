#pragma once
#include "raylib-cpp.hpp"

#include <array>
#include <memory>
#include "utils.h"

enum class BlockName
{
	I_BLOCK,
	J_BLOCK,
	L_BLOCK,
	O_BLOCK,
	S_BLOCK,
	T_BLOCK,
	Z_BLCOK
};

struct BlockLayout
{
	unsigned size;
	std::array<std::array<int, 4>, 4> layout;
	unsigned width;
	unsigned height;
};

class Board;

class Block
{
public:
	Block(const Board& m_board, const BlockName name, const Color& color);

	static std::unique_ptr<Block> createRandomBlock(const Board& m_board);

	void rotateRight();
	void rotateLeft();
	void translate(const raylib::Vector2& translation);
	void draw(const raylib::Vector2& location, bool shallow);

    GETTER(const BlockLayout&, Layout, m_layout)
	GETTER(const raylib::Vector2&, Position, m_position)
	GETTER(const Color&, color, m_color)

private:

    const Board& m_board;
	raylib::Vector2 m_position;
	Color m_color;
	BlockLayout m_layout;
};

