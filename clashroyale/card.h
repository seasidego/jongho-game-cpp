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
    GroundUnit
};



class Card {
public:
    enum class Team {
        None,
        Red,
        Blue,
    };
protected:
    Team team_ = Team::Blue;
    int cost_ = 0;
    float size_ = 0.;
    Vector2 pos_;
    CardType type_;
    AttackType attackType_ = AttackType::None;
    int activeCoolDown_ = 0;

public:
    Card(Team team, int cost, float size, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown);
    virtual ~Card() = default;

public:
    virtual const char* getShape() const;
    virtual float getSize() const;
    const Vector2& getPos() const;
    const Team getTeam() const;

};

class Unit : public Card {
private:
    int hp_ = 0;
    int speed_ = 0;
    int damage_ = 0;
    float attackSpeed_ = 0;
    float firstAttackSpeed_ = 0;
    float range_ = 0;
    float attackRange_ = 0;
    
public:
    Unit(Team team, int cost, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown,
                   int hp, int damage, int speed, float size, float attackSpeed, float firstAttackSpeed, float range, float attackRange);
    ~Unit() = default;

public:
    const char* getShape() const override;
};

class Knight : public Unit {
private:

public:
    Knight(Team team, int x, int y);
    ~Knight() = default;

public:
    const char* getShape() const override;
};

class Building : public Card {
protected:
    int hp_ = 0;
    int damage_ = 0;
    float attackSpeed_ = 0;
    float range_ = 0;

public:
    Building(Team team, int cost, Vector2 pos, CardType type, AttackType attackType, int activeCoolDown,
        int hp, int damage, int size, float attackSpeed, float range);
    virtual ~Building() = default;

public:
    const char* getShape() const override;
};

class PrincessTower : public Building {
private:
    
public:
    PrincessTower(Team team, int x, int y);
    ~PrincessTower() = default;

public:
    const char* getShape() const override;
};

class KingTower : public Building {
private:
    
public:
    KingTower(Team team, int x, int y);
    ~KingTower() = default;

public:
    const char* getShape() const override;
};

class Spell : public Card {
private:
    int damage_ = 0;
    int activeCoolDown_ = 0;
public:
    Spell() = default;
    ~Spell() = default;

public:

};