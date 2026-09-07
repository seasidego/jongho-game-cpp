#pragma once 
#include "raylib.h"

enum class AttackType {
    None,
    Flying,
    Land,
    Building,
    All,
};

enum class CardType {
    None,
    CrownTower,
};



class Card {
protected:
    int cost_ = 0;
    int generationTime_ = 0;
    Vector2 pos_;
    CardType type_;
    AttackType attackType_ = AttackType::None;
    int activeCoolDown_ = 0;

public:
    Card(int cost, int generationTime, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown);
    virtual ~Card() = default;

public:

};

class Unit : public Card {
private:
    int hp_ = 0;
    int speed_ = 0;
    bool fly_ = false;
    int damage_ = 0;
    int attackSpeed_ = 0;
    int range_ = 0;
    
public:
    Unit() = default;
    ~Unit() = default;

public:
    
};

class Building : public Card {
protected:
    int hp_ = 0;
    int damage_ = 0;
    int size_ = 0;
    int attackSpeed_ = 0;
    int range_ = 0;

public:
    Building(int cost, int generationTime, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown,
        int hp, int damage, int size, int attackSpeed, int range);
    virtual ~Building() = default;

public:

};

class PrincessTower : public Building {
private:
    
public:
    PrincessTower();
    ~PrincessTower() = default;

public:

};

class Spell : public Card {
private:
    int damage_ = 0;
    int activeCoolDown_ = 0;
    int area_ = 0;
public:
    Spell() = default;
    ~Spell() = default;

public:

};