#include "card.h"
#include "game.h"

Card::Card(Team team, int cost, float size, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown)  
    : team_(team)
    , cost_(cost)
    , size_(size)
    , pos_(pos)
    , type_(type)
    , attackType_(attackType)
    , activeCoolDown_(activeCoolDown) {}


Building::Building(Team team, int cost, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown,
                   int hp, int damage, int size, float attackSpeed, float range)
    : Card(team, cost, size, pos, type, attackType, activeCoolDown)
    , hp_(hp)
    , damage_(damage)
    , attackSpeed_(attackSpeed)
    , range_(range) {}

PrincessTower::PrincessTower(Team team, int x, int y)
    : Building(team, 0, Vector2{StartPos.x + TileSize * x, StartPos.y + TileSize * y},
        CardType::CrownTower, AttackType::All, 0, 3052, 109, 3, 0.8, 7.5 * TileSize) {}

KingTower::KingTower(Team team, int x, int y)
    : Building(team, 0, Vector2{StartPos.x + TileSize * x, StartPos.y + TileSize * y},
        CardType::CrownTower, AttackType::All, 0, 4824, 109, 4, 1, 7 * TileSize) {}

Unit::Unit(Team team, int cost, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown,
                   int hp, int damage, int speed, float size, float attackSpeed, 
                   float firstAttackSpeed, float range, float attackRange)
    : Card(team, cost, size, pos, type, attackType, activeCoolDown)
    , hp_(hp)
    , damage_(damage)
    , speed_(speed)
    , attackSpeed_(attackSpeed)
    , firstAttackSpeed_(firstAttackSpeed)
    , range_(range) 
    , attackRange_(attackRange) {}
    
Knight::Knight(Team team, int x, int y) 
    :Unit(team, 3, Vector2{StartPos.x + TileSize * x, StartPos.y + TileSize * y},
    CardType::GroundUnit, AttackType::Land, 1, 1,766, 60, 1., 1.2, 0.5, 5.5, 1.2) {}



const char* Card::getShape() const {
    return "?";
}

float Card::getSize() const {
    return size_;
}

const Vector2& Card::getPos() const {
    return pos_;
}

const Card::Team Card::getTeam() const {
    return team_;
}

const char* Building::getShape() const {
    return "B";
}

const char* Unit::getShape() const {
    return "U";
}

const char* PrincessTower::getShape() const {
    return "P";
}

const char* KingTower::getShape() const {
    return "K";
}

const char* Knight::getShape() const {
    return "k";
}
