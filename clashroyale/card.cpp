#include "card.h"
#include "game.h"

Card::Card(int cost, float size, int generationTime, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown)  
    : cost_(cost)
    , size_(size)
    , generationTime_(generationTime)
    , pos_(pos)
    , type_(type)
    , attackType_(attackType)
    , activeCoolDown_(activeCoolDown) {}


Building::Building(int cost, int generationTime, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown,
                   int hp, int damage, int size, float attackSpeed, float range)
    : Card(cost, size, generationTime, pos, type, attackType, activeCoolDown)
    , hp_(hp)
    , damage_(damage)
    , attackSpeed_(attackSpeed)
    , range_(range) {}

PrincessTower::PrincessTower()
    : Building(0, 0, Vector2{100, 100}, CardType::CrownTower, AttackType::All, 0, 3052, 109, 3, 0.8, 7.5 * TileSize) {}
    
const char* Card::getShape() const {
    return "?";
}

float Card::getSize() const {
    return size_;
}

const Vector2& Card::getPos() const {
    return pos_;
}

const char* Building::getShape() const {
    return "B";
}

const char* Unit::getShape() const {
    return "U";
}

const char* PrincessTower::getShape() const {
    return "g";
}
