#include <vector>

class Tile {
private:
    int x_ = 0;
    int y_ = 0;
    
public:
    Tile() = default;
    ~Tile() = default;
};

class Board {
private:
    std::vector<std::vector<Tile>> board_;
    
public:
    Board() = default;
    ~Board() = default;
};

