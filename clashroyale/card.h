#pragma once 

enum class AttackType {
    None,
    Flying,
    Land,
    Building,
    All,
};

class Card {
private:
    int cost_ = 0;
    int generationTime_ = 0;

public:
    Card() = default;
    ~Card() = default;
};

class Unit : public Card {
private:
    int hp_ = 0;
    int speed_ = 0;
    bool fly_ = false;
    int damage_ = 0;
    AttackType attackType_ = AttackType::None;
    int activeCoolDown_ = 0;
    int attackSpeed_ = 0;
    
public:
    Unit() = default;
    ~Unit() = default;
};

class Building : public Card {
private:
    int hp_ = 0;
    int damage_ = 0;
    AttackType attackType_ = AttackType::None;
    int activeCoolDown_ = 0;
    int size_ = 0;
    int attackSpeed_ = 0;

public:
    Building() = default;
    ~Building() = default;
};

class Spell : public Card {
private:
    int damage_ = 0;
    int activeCoolDown_ = 0;
    AttackType attackType_ = AttackType::None;

public:
    Spell() = default;
    ~Spell() = default;
};