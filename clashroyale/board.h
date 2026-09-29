#pragma once 
#include <vector>
#include <memory>
// #include "card.h"
#include "raylib.h"
#include "raymath.h"

// const int BoardWidth = 18;
// const int BoardHight = 32;
const int BoardWidth = 2;
const int BoardHight = 2;

Vector2 toTile(const Vector2& pos);
Vector2 toPos(const Vector2& tile);
bool isEqual(const Vector2& v1, const Vector2& v2);
bool isEqualRoute(const std::vector<Vector2>& v1, const std::vector<Vector2>& v2);

class Tile {
private:
    int x_ = 0;
    int y_ = 0;
    bool canCross_ = 0;

public:
    Tile(bool canMove);
    ~Tile() = default;

public:
    bool canCross() const;
};



class Board {
public:
    using Grid = std::vector<std::vector<Tile>>;    
private:
    Grid grid_;
    
public:
    Board() = default;
    ~Board() = default;
    void init();
    const Grid& getGrid() const;
};

class Card;

class CardMrg {
public:
    using Cards = std::vector<std::unique_ptr<Card>>;
private:
    Cards cards_;

public:
    CardMrg() = default;
    ~CardMrg() = default;

public:
    void init();
    const Cards& getCards() const;
    void moveUnits(const Board& board);
};

 