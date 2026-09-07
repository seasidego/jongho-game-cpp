#include "card.h"

Card::Card(int cost, int generationTime, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown)  
    : cost_(cost)
    , generationTime_(generationTime)
    , pos_(pos)
    , type_(type)
    , attackType_(attackType)
    , activeCoolDown_(activeCoolDown) {}


Building::Building(int cost, int generationTime, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown,
                   int hp, int damage, int size, int attackSpeed, int range)
    : Card(cost, generationTime, pos, type, attackType, activeCoolDown)
    , hp_(hp)
    , damage_(damage)
    , size_(size)
    , attackSpeed_(attackSpeed)
    , range_(range) {}

