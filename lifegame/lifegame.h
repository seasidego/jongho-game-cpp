#include <iostream>
#include <memory>
#include <sys/stat.h>
#include <utility>
#include <vector>
#include <map>
#include <random>
#include <set>

enum class ConditionType {
    Alive,
    Dead
};

class Grid;

class Cell {
private:
    ConditionType condition_ = ConditionType::Dead;
    ConditionType willChange_ = ConditionType::Dead;
    int x_ = 0;
    int y_ = 0;
public:
    Cell(ConditionType c, int x, int y) : condition_(c), x_(x), y_(y) {};
    ConditionType getCondition() const;
    void setCondition(ConditionType c);
    void caculateLive(const Grid& grid);
    void changeCondition();
};

class Grid {
private:
    std::vector<std::vector<Cell>> grid_;
public:
    void initGrid();
    void start();
    void print() const;
    std::vector<Cell>  getNearCells(int x, int y) const;
    void setAlive(int x, int y);
};