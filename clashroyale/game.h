#pragma once 
#include "player.h"
#include "board.h"
#include "card.h"
#include "raylib.h"
#include <map>

const float TileSize = 20;
const Vector2 StartPos{30, 30};

class UIMgr {
private:

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
    bool run_ = true;

public:
    Game() = default;
    ~Game() = default;

public:
    // void startUI();
    void init();
    const UIMgr& getUIMgr() const ;
    void play();
    void moveUnit();

};
