#include "board.h"
#include "card.h"
#include "player.h"

void Board::init() {
    for (int i = 0; i < 32; i++) {
        board_.emplace_back(std::vector<Tile>(18));
    }
}

const Board::Grid& Board::getBoard() const {
    return board_;
}

void CardMrg::init() {
    cards_.emplace_back(std::make_unique<PrincessTower>());
}

const CardMrg::Cards& CardMrg::getCards() const {
    return cards_;
}