#include "lifegame.h"
#include <format>
#include <cstdlib>
#include <random>

std::ostream& operator<<(std::ostream& os, ConditionType condition) {
    switch (condition) {
        case ConditionType::Alive: os << "*"; break;
        case ConditionType::Dead:  os << " ";  break;
        default: os << static_cast<int>(condition); break;
        //default:                   os << "Unknown"; break;
    }
    return os; // 연속 출력을 위해 스트림 참조를 반환합니다.
}

void Grid::initGrid(int size) {
    for (int i = 0; i < size; i++) {
        std::vector<Cell> cellLine;
        for (int j = 0; j < size; j++) {
            cellLine.emplace_back(Cell(ConditionType::Dead, i, j));
        }    
        grid_.emplace_back(cellLine);
    }
}

void Grid::initGridRandom(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < size; i++) {
        std::vector<Cell> cellLine;
        for (int j = 0; j < size; j++) {
            std::uniform_int_distribution<int> random(0, 1);

            if (random(gen) == 1) {
                cellLine.emplace_back(Cell(ConditionType::Alive, i, j));
            } else {
                cellLine.emplace_back(Cell(ConditionType::Dead, i, j));
            }            
        }    
        grid_.emplace_back(cellLine);
    }
}

void Grid::initSpaceGliderGun() {
    std::vector<std::string> pattern = {
        "....................................",
        "........................X...........",
        "......................X.X...........",
        "............XX......XX............XX",
        "...........X...X....XX............XX",
        "XX........X.....X...XX............",
        "XX........X...X.XX....X.X.........",
        "..........X.....X.......X..........",
        "...........X...X....................",
        "............XX......................"
    };

    int size = 50;
    for (int i = 0; i < size; i++) {
        std::vector<Cell> cellLine;
        for (int j = 0; j < size; j++) {
            std::uniform_int_distribution<int> random(0, 1);
            cellLine.emplace_back(Cell(ConditionType::Dead, i, j));
        }    
        grid_.emplace_back(cellLine);
    }

    for (int y = 0; y < pattern.size(); ++y) {
        for (int x = 0; x < pattern[y].size(); ++x) {
            if (pattern[y][x] == 'X') {
                grid_[5 + y][5 + x].setCondition(ConditionType::Alive);
            }
        }
    }
}

void Grid::setAlive(int x, int y) {
    if (x < 0 || x >= grid_.size()) {
        return;
    }
    if (y < 0 || y >= grid_.size()) {
        return;
    }
    grid_[x][y].setCondition(ConditionType::Alive);
}

void Grid::start() {
    std::for_each(grid_.begin(), grid_.end(), [this](auto& cellLine) {
        std::for_each(cellLine.begin(), cellLine.end(), [this](auto& cell) {
            cell.caculateLive(*this);
        });
    });

    std::for_each(grid_.begin(), grid_.end(), [](auto& cellLine) {
        std::for_each(cellLine.begin(), cellLine.end(), [](auto& cell) {
           cell.changeCondition();
        });
    });
}

ConditionType Cell::getCondition() const {
    return condition_;
}

void Cell::setCondition(ConditionType c) {
    condition_ = c;
}

void Cell::caculateLive(const Grid& grid) {
    auto cells = grid.getNearCells(x_, y_);
    int alive = 0;
    int dead = 0;
    std::for_each(cells.begin(), cells.end(), [&](const auto& cell){
        if (cell.condition_ == ConditionType::Alive) {
            alive++;
        } else if (cell.condition_ == ConditionType::Dead) {
            dead++;
        }
    });
    if (condition_ == ConditionType::Alive) {
        if (alive >= 2 && alive <= 3) {
            willChange_ = ConditionType::Alive;
        } else {
            willChange_ = ConditionType::Dead;
        }
    } else {
        if (alive == 3) {
            willChange_ = ConditionType::Alive;
        }
    }
}

void Cell::changeCondition() {
    condition_ = willChange_;
}

void Grid::print() const {
    std::system("clear");

    int row = 0;
    std::for_each(grid_.begin(), grid_.end(), [&row](const auto& cellLine) {
        std::cout << std::format("{:3}", row)  << ": ";
        std::for_each(cellLine.begin(), cellLine.end(), [](const auto& cell) {
            std::cout << cell.getCondition() << " ";
        });
        std::cout << std::endl;
        row++;
    });
    // std::cout << "------------------------" << std::endl;
}

std::vector<Cell> Grid::getNearCells(int x, int y) const {
    std::vector<Cell> cells;
    int xp = 0;
    int yp = 0;
    for (int i = -1; i <= 1; i++) {
        xp = x + i; 
        if (xp < 0 || xp >= grid_.size()) {
            continue;
        }
        for (int j = -1; j <= 1; j++) {
            yp = y + j; 
            if (yp < 0 || yp >= grid_[xp].size()) {
                continue;
            }
            if (xp == x && yp == y) {
                continue; //dont add it
            }
            cells.emplace_back(grid_[xp][yp]);
        }    
    }
    return cells;
}
