#pragma once
#include "board.h"
#include "raylib.h"

class Nav {
private:

public:
    std::vector<Vector2> nav(const Board& board, const Vector2& currentPos, const Vector2& destPos);

public:
    Nav() = default;
    ~Nav() = default;
};