#include "board.h"
#include "card.h"
#include "player.h"

Tile::Tile(bool canCross) : canCross_(canCross) {}

bool Tile::canCross() const {
    return canCross_;
}

void Board::init() {
    for (int i = 0; i < BoardHight; i++) {
        grid_.emplace_back(std::vector<Tile>{});
        for (int j = 0; j < BoardWidth; j++) {
            if (i == 15 || i == 16) {
                if (j == 3 || j == 4 || j == 13 || j == 14) {
                    grid_[i].emplace_back(Tile(true));
                } else {
                    grid_[i].emplace_back(Tile(false));
                }
            } else {
                grid_[i].emplace_back(Tile(true));
            }
        }
    }
}

const Board::Grid& Board::getGrid() const {
    return grid_;
}

void CardMrg::moveUnits(const Board& board) {
    std::for_each(cards_.begin(), cards_.end(), [&board](auto& u) {
        u->move(board);
    });
}

void CardMrg::init() {
    cards_.emplace_back(std::make_unique<PrincessTower>(Card::Team::Blue, 2, 24));
    cards_.emplace_back(std::make_unique<PrincessTower>(Card::Team::Blue, 13, 24));
    cards_.emplace_back(std::make_unique<KingTower>(Card::Team::Blue, 7, 27));
    cards_.emplace_back(std::make_unique<PrincessTower>(Card::Team::Red, 2, 5));
    cards_.emplace_back(std::make_unique<PrincessTower>(Card::Team::Red, 13, 5));
    cards_.emplace_back(std::make_unique<KingTower>(Card::Team::Red, 7, 1));

    cards_.emplace_back(std::make_unique<KingTower>(Card::Team::Red, 10, 10));

    cards_.emplace_back(std::make_unique<Knight>(Card::Team::Blue, 10, 24));
    // cards_.emplace_back(std::make_unique<Knight>(Card::Team::Red, 10, 10));
}

const CardMrg::Cards& CardMrg::getCards() const {
    return cards_;
}