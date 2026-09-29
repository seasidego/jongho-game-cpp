#pragma once
#include "board.h"
#include "raylib.h"

class Nav {
private:

public:
    // std::vector<Vector2> nav(const Board& board, const Vector2& currentPos, const Vector2& destPos);
    std::vector<Vector2> nav(const Board::Grid& grid, const Vector2& currentPos, const Vector2& destPos);
    std::vector<Vector2> navPart(const Board::Grid& grid, const Vector2& currentPos, 
        const Vector2& destPos, std::vector<Vector2> route, int depth);

public:
    Nav() = default;
    ~Nav() = default;
};