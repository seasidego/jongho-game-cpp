#pragma once 
#include <vector>
#include <memory>
// #include "card.h"

const int BoardWidth = 18;
const int BoardHight = 32;


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
    using Grid = std::vector<std::vector<Tile>>;
private:
    Grid board_;
    
public:
    Board() = default;
    ~Board() = default;
    void init();
    const Grid& getBoard() const;
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

};

