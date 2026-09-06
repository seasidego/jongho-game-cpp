#include "card.h"

class Playar {
private:
    int elixir_ = 0;
    int elixirGenerationTime_ = 0;

public:
    Playar() = default;
    ~Playar() = default;   
};

class CrownTower : Card {
private:
    int hp_ = 0;
    int damage_ = 0;
    int attackSpeed_ = 0;
public:
    CrownTower() = default;
    ~CrownTower() = default;
};