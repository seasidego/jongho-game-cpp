#include "board.h"
#include "card.h"
#include "player.h"

void Board::init() {
    for (int i = 0; i < BoardHight; i++) {
        board_.emplace_back(std::vector<Tile>(BoardWidth));
    }
}

const Board::Grid& Board::getBoard() const {
    return board_;
}

void CardMrg::init() {
    cards_.emplace_back(std::make_unique<PrincessTower>(2, 24));
    cards_.emplace_back(std::make_unique<PrincessTower>(13, 24));
    cards_.emplace_back(std::make_unique<KingTower>(7, 27));
}

const CardMrg::Cards& CardMrg::getCards() const {
    return cards_;
}