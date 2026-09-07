#include "board.h"
#include "card.h"
#include "player.h"

void Board::init() {
    for (int i = 0; i < 32; i++) {
        board_.emplace_back(std::vector<Tile>(18));
    }
}

const Board::board& Board::getBoard() const {
    return board_;
}

void CardMrg::init() {
    
    // CrownTower c(0, 0, Vector2{30, 30}, CardType::CrownTower, AttackType::All, 0, CrownTowerHP, );
    // cards_.emplace_back(c);
}