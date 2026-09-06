#include "board.h"

void Board::init() {
    for (int i = 0; i < 32; i++) {
        board_.emplace_back(std::vector<Tile>(18));
    }
}

const Board::board& Board::getBoard() const {
    return board_;
}