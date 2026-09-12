#pragma once 
#include "player.h"
#include "board.h"
#include "card.h"
#include "raylib.h"
#include <map>

const float TileSize = 20;

class UIMgr {
private:
    bool run_ = true;
    Vector2 startPos_{30, 30};

public:
    UIMgr() = default;
    ~UIMgr() = default;

public:
    void init();
    void print(const Board& b, const CardMrg& mrg) const;
    void printBoard(const Board& b, const CardMrg& mrg) const;
    void stop();
};

class Game {
private:
    Playar player_;
    Board board_;
    UIMgr uiMgr_;
    CardMrg cardMgr_;

public:
    Game() = default;
    ~Game() = default;

public:
    // void startUI();
    void init();
    void endUI();
    const UIMgr& getUIMgr() const ;
    void print();

};
