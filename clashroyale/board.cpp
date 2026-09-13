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
    cards_.emplace_back(std::make_unique<PrincessTower>(Card::Team::Blue, 2, 24));
    cards_.emplace_back(std::make_unique<PrincessTower>(Card::Team::Blue, 13, 24));
    cards_.emplace_back(std::make_unique<KingTower>(Card::Team::Blue, 7, 27));
    cards_.emplace_back(std::make_unique<PrincessTower>(Card::Team::Red, 2, 5));
    cards_.emplace_back(std::make_unique<PrincessTower>(Card::Team::Red, 13, 5));
    cards_.emplace_back(std::make_unique<KingTower>(Card::Team::Red, 7, 1));
    cards_.emplace_back(std::make_unique<Knight>(Card::Team::Red, 10, 10));
}

const CardMrg::Cards& CardMrg::getCards() const {
    return cards_;
}