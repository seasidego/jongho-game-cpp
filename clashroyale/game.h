#pragma once 
#include "player.h"
#include "board.h"
#include "card.h"

class UIMgr {
private:
    bool run_ = true;
    int startX_ = 30;
    int startY_ = 30;
    int tileSize_ = 20;

public:
    UIMgr() = default;
    ~UIMgr() = default;

public:
    void init();
    void print(const Board& b) const;
    void printBoard(const Board& b) const;
    void stop();
};

class Game {
private:
    Playar player_;
    Board board_;
    UIMgr UIMgr_;

public:
    Game() = default;
    ~Game() = default;

public:
    void startUI();
    void endUI();
    const UIMgr& getUIMgr() const ;
    void print();

};

