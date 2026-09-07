#pragma once 
#include <vector>
#include <memory>
// #include "card.h"

class Tile {
private:
    int x_ = 0;
    int y_ = 0;
    
public:
    Tile() = default;
    ~Tile() = default;
};


class Board {
public:
    using board = std::vector<std::vector<Tile>>;
private:
    board board_;
    
public:
    Board() = default;
    ~Board() = default;
    void init();
    const board& getBoard() const;
};

class Card;

class CardMrg {
private:
    std::vector<std::unique_ptr<Card>> cards_;

public:
    CardMrg() = default;
    ~CardMrg() = default;

public:
    void init();

};

